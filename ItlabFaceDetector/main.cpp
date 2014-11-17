#include "Detector.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

class TestClassifier: public Classifier
{
public:
    TestClassifier()
    {}
    virtual int Classify(const Mat &img)
    {
        return rand() % 2;
    }
    virtual ~TestClassifier()
    {}
};

int main()
{
    Detector detector;
    Mat img = imread("test.jpg", 1);
    vector<Rect> rects;
    vector<float> scores;
    Ptr<Classifier> classiefier = Ptr<Classifier>(new TestClassifier());

    detector.Detect(img, rects, scores, classiefier, Size(20, 20), 2, 2, 1.5);

    cout << "Count annotated rects is " << rects.size() << endl;
    cout << "It's test Faces Detector." << endl;
    return 0;
}