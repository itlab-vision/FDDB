#ifndef _DETECTOR_HPP_
#define _DETECTOR_HPP_

#include "Classifier.hpp"
#include <vector>
#include <opencv2/core/core.hpp>

const float DETECTOR_THRESHOLD = 0.001f;

class Detector
{
public:
    void Detect(const cv::Mat &img, std::vector<int> &labels, std::vector<float> &scores,
    			std::vector<cv::Rect> &rects,  cv::Ptr<Classifier> classifier, 
    			cv::Size windowSize = cv::Size(20, 20), int dx = 1, int dy = 1, double scale = 1.2,
    			int minNeighbors = 3, bool groupRect = false, bool preproc = false);  
private:
	void Preprocessing(cv::Mat &img);
};

#endif
