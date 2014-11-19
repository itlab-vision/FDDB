#include "Detector.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void Detector::Detect(const Mat &img, vector<int> &labels, vector<float> &scores, vector<Rect> &results, 
					  const Ptr<Classifier> classifier, Size windowSize, int dx, int dy, double scale)
{
    CV_Assert(scale > 1.0 && scale < 2.0);

    results.clear();
    scores.clear();
    //fill image pyramid
    vector<Mat> imgPyramid;
    Mat tmp;
    img.copyTo(tmp);
    //resize version
    while (tmp.cols >= windowSize.width && tmp.rows >= windowSize.height)
    {
        imgPyramid.push_back(tmp);
        resize(tmp, tmp, Size((int)(tmp.cols / scale), (int)(tmp.rows / scale)), 0, 0, INTER_LINEAR);
    }
    //for every layer of pyramid
    cout << imgPyramid.size() << endl;
    for (int i = 0; i < imgPyramid.size(); i++)
    {
        Mat layer = imgPyramid[i];
        cout << layer.rows << " " << layer.cols << endl;
        for (int y = 0; y < layer.rows - windowSize.height; y += dy)
        {
            for (int x = 0; x < layer.cols - windowSize.width; x += dx)
            {
                Rect rect(x, y, windowSize.width, windowSize.height);
                Mat window = layer(rect);
                Result result = classifier->Classify(window);
                classes.push_back(result.label);
                scores.push_back(result.confidence);
                results.push_back(rect);
            }
        }
    }
}