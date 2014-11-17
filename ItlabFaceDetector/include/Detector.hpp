#include "Classifier.hpp"
#include <vector>
#include <memory>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

class FaceDetector
{
public:
    void Detect(Mat img, vector<Rect> &results, Classifier *classifier, Size windowSize = Size(20, 20), int dx = 1, int dy = 1, double scale = 1.2);    
};