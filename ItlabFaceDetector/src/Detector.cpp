#include "Detector.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void Detector::Detect(const Mat &img, vector<int> &labels, vector<float> &scores, vector<Rect> &rects, 
                      Ptr<Classifier> classifier, Size windowSize, int dx, int dy, double scale, bool groupRect)
{
    CV_Assert(scale > 1.0 && scale <= 2.0);

    rects.clear();
    scores.clear();
    //fill image pyramid
    vector<Mat> imgPyramid;
    Mat tmp;
    img.copyTo(tmp);
    //create pyramid
    while (tmp.cols >= windowSize.width && tmp.rows >= windowSize.height)
    {
        imgPyramid.push_back(tmp);
        resize(tmp, tmp, Size((int)(tmp.cols / scale), (int)(tmp.rows / scale)), 0, 0, INTER_LINEAR);
    }
    //labels.reserve(100000);
    //scores.reserve(100000);
    //rects.reserve(100000);
    float newScale = 1;
    //for every layer of pyramid
    for (int i = 0; i < imgPyramid.size(); i++)
    {
        Mat layer = imgPyramid[i];
        vector<Rect> layerRect;
        cout << i << endl;
        for (int y = 0; y < layer.rows - windowSize.height + 1; y += dy)
        {
            for (int x = 0; x < layer.cols - windowSize.width + 1; x += dx)
            {
                Rect rect(x, y, windowSize.width, windowSize.height);
                Mat window = layer(rect);

                Result result = classifier->Classify(window);
                //if (fabs(result.confidence) < DETECTOR_THRESHOLD)
                if (fabs(result.confidence) == 0)
                {
                    //cout << result.confidence << endl;
                    labels.push_back(result.label);
                    scores.push_back(result.confidence2);
                
                    rect.x *= newScale;
                    rect.y *= newScale;
                    rect.width *= newScale;
                    rect.height *= newScale;

                    layerRect.push_back(rect);
                }
            }
        }
        if (groupRect)
        {
            groupRectangles(layerRect, 1, 0.2);
        }
        rects.insert(rects.end(), layerRect.begin(), layerRect.end());
        newScale *= scale;
    }
}