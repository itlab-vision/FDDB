#include "Classifier.hpp"

class DigitClassifier : public Classifier {
public:
	DigitClassifier() {}

    virtual int Classify(const cv::Mat& img);

    virtual ~DigitClassifier() {}
};