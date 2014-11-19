#include <iostream>
#include <cstdlib>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "DigitClassifier.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("1.png", 0);

    Ptr<Classifier> classifier = Ptr<Classifier>(new DigitClassifier());
	int result = classifier->Classify(img);

	return 0;
}
