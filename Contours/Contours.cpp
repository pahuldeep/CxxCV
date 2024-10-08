#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    string source_path = "../asset/source.jpg";
    string result_path = "../asset/result.jpg";

    Mat image = imread(source_path);
    Mat imgGray;

    cvtColor(image, imgGray, COLOR_BGR2GRAY);

    Mat edges;
    Canny(image, edges, 100.0, 200.0, 3);

    vector<vector<Point> > contours;

    int mode = RETR_TREE;
    int method = CHAIN_APPROX_TC89_KCOS;

    findContours(edges, contours, mode, method);

    RNG rng(12345); // any random number
    Mat result(edges.size(), CV_8UC3, Scalar(0));

    int thickness = 2;
    int thresholdArea = 30;


    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

        if(contourArea(contours[i]) > thresholdArea){
            drawContours(result, contours, i, color, thickness);
        }
    }

    imshow("Display", result);
    imwrite(result_path, result);

    waitKey(0);
    destroyAllWindows();

}
