#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

#include "Detector.hpp"
#include "DigitClassifier.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg", 1);
	
	DigitClassifier *classifier = new Classifier();
	float result = classifier->Classify(img);

	if (result == 0.0f) {
		imshow("Test passed", img);
	}
	return 0;
}