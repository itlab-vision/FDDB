#include "Classifier.hpp"

class DigitClassifier : public Classifier {
public:
	DigitClassifier() {}

    virtual Result Classify(const cv::Mat& img);

    virtual ~DigitClassifier() {}
};