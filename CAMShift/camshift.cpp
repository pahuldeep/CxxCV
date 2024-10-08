#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

TermCriteria criteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 20, 1.0);

bool selecting = false;

Rect selection;
Point spo;

void onMouse(int event, int x, int y, int, void*)
{
    switch(event)
    {
    case EVENT_LBUTTONDOWN:
    {
        spo.x = x;
        spo.y = y;
        selection.x = spo.x;
        selection.y = spo.y;
        selection.width = 0;
        selection.height = 0;
        selecting = true;
    } break;
    case EVENT_LBUTTONUP:
    {
        selecting = false;
    } break;
    default:
    {
        selection.x = min(x, spo.x);
        selection.y = min(y, spo.y);
        selection.width = abs(x - spo.x);
        selection.height = abs(y - spo.y);
    } break;
    }
}

int main()
{
    VideoCapture cam(0);

    if(!cam.isOpened()){
        return -1;
    }
    Rect searchWindow;

    namedWindow("Display");
    cv::setMouseCallback("Display", onMouse);

    vector<Point> route;
    Mat histogram, backProject, mask;

    int key = -1;

    // // Default resolutions of the frame are obtained.The default resolutions are system dependent.
    // int frame_width = int(cam.get(cv::CAP_PROP_FRAME_WIDTH));
    // int frame_height = int(cam.get(cv::CAP_PROP_FRAME_HEIGHT));

    // // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    // VideoWriter output_cap("out.mp4", cv::VideoWriter::fourcc('M', 'P', '4', '2'), 32.0, Size(frame_width, frame_height));



    while(key != 27)
    {
        Mat frame;
        cam >> frame;
        if(frame.empty())
            break;

        Mat frameHsv, hue;
        vector<Mat> hsvChannels;
        cvtColor(frame, frameHsv, COLOR_BGR2HSV);
        split(frameHsv, hsvChannels);
        hue = hsvChannels[0];

        int bins = 120;
        int nimages = 1;
        int channels[] = {0};
        float rangeHue[] = {0, 180};
        const float* ranges[] = {rangeHue};

        int histSize[] = { bins };

        bool uniform = true;

        if(selecting && selection.area() > 0)
        {
            Mat sel(frame, selection);

            int lbHue = 00 , hbHue = 180;
            int lbSat = 30 , hbSat = 256;
            int lbVal = 30 , hbVal = 230;

            inRange(frameHsv, Scalar(lbHue, lbSat, lbVal), Scalar(hbHue, hbSat, hbVal), mask);

            Mat roi(hue, selection);
            Mat maskroi(mask, selection);

            calcHist(&roi, nimages, channels, maskroi, histogram, 1, histSize, ranges, uniform);

            normalize(histogram, histogram, 0, 255, NORM_MINMAX);

            bitwise_not(sel, sel);

            searchWindow = selection;
        }
        else if(!histogram.empty())
        {
            double scale = 1.0;
            calcBackProject(&hue, nimages, channels, histogram, backProject, ranges, scale, uniform);

            erode(backProject, backProject, Mat());

            CamShift(backProject, searchWindow, criteria);

            Point p(searchWindow.x + searchWindow.width/2, searchWindow.y + searchWindow.height/2);

            route.push_back(p);
            if(route.size() > 60){
                route.erase(route.begin());
            }

            rectangle(frame, searchWindow, Scalar(0,0,255), 2);
            polylines(frame, route, false, Scalar(0,255,0), 2);

            cvtColor(backProject, backProject, COLOR_GRAY2BGR);

            rectangle(backProject, searchWindow, Scalar(0,0,255), 2);
            polylines(backProject, route, false, Scalar(0,255,0), 2);
        }

        switch(key)
        {
        case 'b':
            if(!backProject.empty()) {
                imshow("Display", backProject);
                // output_cap.write(backProject);

            }
            else {
                imshow("Display", frame);
                // output_cap.write(frame);
            }
            break;

        case 'v': default:
            imshow("Display", frame);
            // output_cap.write(frame);
            break;
        }

        int k = waitKey(10);
        if(k > 0){
            key = k;
        }

    }
    cam.release();

    // output_cap.release();

    return 0;
}
