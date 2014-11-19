#include <iostream>
#include <cstdlib>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "DigitClassifier.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/imgs/mnist_originals.png", 0);

    Ptr<Classifier> classifier = Ptr<Classifier>(new DigitClassifier());
	//Result result = classifier->Classify(img);
	
	Detector detector;
	vector<Rect> results;
	vector<float> scores;
	vector<int> classes;

	detector.Detect(img, classes, results, scores, classifier, Size(28, 28), 28, 28, 1.2);
	cout << classes.size() << endl;
	for (int i = 0; i < classes.size() - 1; i++)
	{
		if (classes[i] == 5 && classes[i + 1] == 4)
			cout << "asdasdas" << endl;
		cout << classes[i] << " ";
	}
	cout << endl;
	
	//cout <<"It's " << result.label << " with confidence = " << result.confidence << endl;

	return 0;
}
