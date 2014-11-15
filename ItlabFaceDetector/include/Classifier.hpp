#include <opencv2/core.hpp>

using namespace cv;

class FaceClassifier
{
public:
	FaceClassifier();

    virtual int Classify(Mat img) = 0;

    virtual ~FaceClassifier();
};