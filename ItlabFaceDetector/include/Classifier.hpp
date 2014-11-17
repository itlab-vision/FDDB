#include <opencv2/core.hpp>

using namespace cv;

class Classifier
{
public:
	Classifier();

    virtual float Classify(const Mat& img) = 0;

    virtual ~Classifier();
};