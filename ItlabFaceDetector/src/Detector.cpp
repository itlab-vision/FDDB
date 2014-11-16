#include "Detector.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

void FaceDetector::Detect(Mat img, vector<Rect> &results, FaceClassifier *classifier, Size windowSize, int dx, int dy, double scale)
{
	results.clear();
	//fill image pyramid
	vector<Mat> imgPyramid;
	Mat tmp;
	img.copyTo(tmp);
	Mat dst = tmp;
	//pyrDown version
	/*
	while (tmp.cols >= windowSize.width && tmp.rows >= windowSize.height)
	{
		imgPyramid.push_back(tmp);
		pyrDown(tmp, dst, Size((int)(tmp.cols / scale), (int)(tmp.rows / scale)));
		tmp = dst;
	}
	*/
	//resize version
	while (tmp.cols >= windowSize.width && tmp.rows >= windowSize.height)
	{
		imgPyramid.push_back(tmp);
		resize(tmp, dst, Size((int)(tmp.cols / scale), (int)(tmp.rows / scale)), 0, 0, INTER_LINEAR);
		tmp = dst;
	}
	cout << imgPyramid.size() << endl;
	//for every layer of pyramid
	for (int i = 0; i < imgPyramid.size(); i++)
	{
		Mat layer = imgPyramid[i];
		for (int y = 0; y < layer.rows - windowSize.height; y += dy)
		{
			for (int x = 0; x < layer.cols - windowSize.width; x += dx)
			{
				Rect rect(x, y, windowSize.width, windowSize.height);
				Mat window = layer(rect);
				int predictedLabel = classifier->Classify(window);
				if (predictedLabel)
				{
					results.push_back(rect);
				}
			}
		}
	}
}