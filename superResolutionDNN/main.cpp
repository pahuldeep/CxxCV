#include <opencv2/opencv.hpp>
#include <opencv2/dnn_superres.hpp>

using namespace std;

using namespace cv;
using namespace dnn;
using namespace dnn_superres;

Mat upscaleImage(Mat img, string modelName, string modelPath, int scale){

    DnnSuperResImpl sr;

    sr.readModel(modelPath);
    sr.setModel(modelName, scale);

    // Output image
    Mat outputImage;
    sr.upsample(img, outputImage);

    return outputImage;
}

int main(int argc, char *argv[])
{
    Mat img = imread("../../res/sample.png");

    // EDSR (x4)
    string path = "../../EDSR_x4.pb";
    string modelName = "edsr";

    int scale = 4;
    Mat result = upscaleImage(img, modelName, path, scale);

    // imshow("Original image",img);
    // imshow("SR upscaled",result);

    imwrite("../../result.png", result);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
