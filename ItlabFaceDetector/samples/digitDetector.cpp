#include <iostream>
#include <cstdlib>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "DigitClassifier.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("/imgs/testMnist.png", IMREAD_COLOR);
	Mat grayImg;
	cvtColor(img, grayImg, COLOR_BGR2GRAY);

	Ptr<Classifier> classifier = Ptr<Classifier>(new DigitClassifier());
	
	Detector detector;
	vector<Rect> rects;
	vector<float> scores;
	vector<int> labels;

	detector.Detect(grayImg, labels, scores, rects, classifier, Size(28, 28), 1, 1, 1.2, true);

	for (int i = 0; i < rects.size(); i++)
	{
		rectangle(img, rects[i], Scalar(0, 0, 255));
	}

	imwrite("result.jpg", img);

	return 0;
}
