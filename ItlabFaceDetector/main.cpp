#include "Detector.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

class TestClassifier: public FaceClassifier
{
public:
	TestClassifier()
	{}
	virtual int Classify(Mat img)
	{
		return rand() % 2;
	}
	virtual ~TestClassifier()
	{}
};

int main()
{
	FaceDetector detector;
	Mat img = imread("test.jpg", 1);
	vector<Rect> rects;
	//Ptr<FaceClassifier> classiefier = new TestClassifier();
	FaceClassifier *classiefier = new TestClassifier();

	detector.Detect(img, rects, classiefier, Size(20, 20), 2, 2, 1.2);

	cout << "Count annotated rects is " << rects.size() << endl;
	cout << "It's test Faces Detector." << endl;
	return 0;
}