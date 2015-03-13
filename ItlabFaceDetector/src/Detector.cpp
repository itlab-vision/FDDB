#include "Detector.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void Detector::Preprocessing(Mat &img)
{
    float mean[] = {0.40559885502486, -0.019621851500929, 0.026953143125972};
    float std[] = {0.26126178026709, 0.049694558439293, 0.071862255292542};
    img.convertTo(img, CV_32F, 1.0f/255.0f);
    cvtColor(img, img, COLOR_BGR2YCrCb);

    for (int x = 0; x < img.cols; x++)
    {
        for (int y = 0; y < img.rows; y++)
        {
            Vec3f pixel = img.at<Vec3f>(y, x);
            for (int z = 0; z < 3; z++)
            {
                pixel[z] = (pixel[z] - mean[z]) / std[z];
            }
        }
    }
}

void Detector::Detect(const Mat &img, vector<int> &labels, vector<double> &scores, vector<Rect> &rects, 
                      Ptr<Classifier> classifier, Size windowSize, int dx, int dy, double scale,
                      int minNeighbors, bool groupRect)
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

    for (uint i = 0; i < imgPyramid.size(); i++)
    {
        Mat layer = imgPyramid[i];
        vector<Rect> layerRect;

        for (int y = 0; y < layer.rows - windowSize.height + 1; y += dy)
        {
            for (int x = 0; x < layer.cols - windowSize.width + 1; x += dx)
            {
                Rect rect(x, y, windowSize.width, windowSize.height);
                Mat window = layer(rect);

                Result result = classifier->Classify(window);
                if (fabs(result.confidence) < DETECTOR_THRESHOLD && result.label == 1)
                {
                    labels.push_back(result.label);
                    scores.push_back(result.confidence);

                    layerRect.push_back( Rect(cvRound(rect.x * newScale), cvRound(rect.y * newScale), 
                                              cvRound(rect.width * newScale), cvRound(rect.height * newScale)) );
                }
            }
        }
        if (groupRect)
        {
            groupRectangles(layerRect, minNeighbors, 0.2);
        }
        rects.insert(rects.end(), layerRect.begin(), layerRect.end());
        newScale *= scale;
    }
}