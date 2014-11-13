#include <opencv2/core.hpp>

using namespace cv;

class FaceClassifier
{
public:
    virtual int Classify(Mat img) = 0;
};