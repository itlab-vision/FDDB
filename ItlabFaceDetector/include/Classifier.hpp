#ifndef _CLASSIFIER_HPP_
#define _CLASSIFIER_HPP_

#include <opencv2/core/core.hpp>

struct Result
{
	int label;
	float confidence;
};

class Classifier
{
public:
    Classifier();

    virtual Result Classify(const cv::Mat &img) = 0;

    virtual ~Classifier();
};

#endif