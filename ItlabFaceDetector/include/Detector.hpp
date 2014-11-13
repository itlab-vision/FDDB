#include "Classifier.hpp"
#include <vector>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

class FaceDetector
{
public:
    vector<Rect> Detect(Mat img, Size minSize, Size maxSize, int step);
private:
    Ptr<FaceClassifier> classifier;
};