#include <opencv2/core.hpp>

class Classifier
{
public:
    Classifier();

    virtual int Classify(const cv::Mat &img) = 0;

    virtual ~Classifier();
};