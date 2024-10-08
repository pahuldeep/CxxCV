#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void color_switch(){

    cv::VideoCapture cam(0);
    if(!cam.isOpened()){ cout << "check again camera is not working i think! "; }

    int key = -1;

    while((key != ' ') & (key != 27)){
        cv::Mat frame;
        cam >> frame;

        if(frame.empty()){ break; }

        switch (key) {
        case '1':
            cv::applyColorMap(frame, frame, cv::COLORMAP_JET);
            break;
        case '2':
            cv::applyColorMap(frame, frame, cv::COLORMAP_HOT);
            break;
        case '3':
            cv::applyColorMap(frame, frame, cv::COLORMAP_COOL);
            break;
        case '4':
            cv::applyColorMap(frame, frame, cv::COLORMAP_BONE);
            break;
        case '5':
            cv::applyColorMap(frame, frame, cv::COLORMAP_HSV);
            break;

        default:
            std::cerr << "Invalid colormap choice" << std::endl;
            break;
        }
        cv::imshow("Camera", frame);

        int k = cv::waitKey(10);

        if(k > 0)
            key = k;
    }
    cam.release();
}

int main()
{
    color_switch();
}
