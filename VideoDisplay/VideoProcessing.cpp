#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void edge_detection(){
    cv::VideoCapture cam(0);
    if(!cam.isOpened()){ cout << "check again camera is not working i think! "; }

    int key = -1;

    while(key != 'q'){
        cv::Mat frame;
        cam >> frame;

        if(frame.empty()){ break; }

        cv::Mat edges;

        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, cv::Size(5, 5), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);

        cv::imshow("Camera", edges);

        int k = cv::waitKey(10);
        if(k > 0) key = k;
    }
    cam.release();
}

int main()
{
    edge_detection();
}
