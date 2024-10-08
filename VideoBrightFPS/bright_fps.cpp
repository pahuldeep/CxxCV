#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void darkfps(){
    
    cv::VideoCapture cam(0);
    if(!cam.isOpened()){ cout << "check again camera is not working i think! "; }

    int key = -1;
    vector<cv::Scalar> points;

    while((key != ' ') & (key != 27)){

        cv::Mat frame;
        cam >> frame;

        if(frame.empty()){ break; }

        if(points.size() > 120 ){ points.erase(points.begin()); }

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        points.push_back(mean(gray));
        cv::Scalar points_all = mean(points);

        cv::putText(frame, to_string(points_all[0]),
                    cv::Point(0, frame.rows -1),
                    cv::FONT_HERSHEY_PLAIN, 1.0,
                    cv::Scalar(0, 255, 0)
                    );

        cv::imshow("Camera", frame);

        int k = cv::waitKey(10);
        if(k > 0) key = k;
    }
    cam.release();
}

int main()
{
    darkfps();
}
