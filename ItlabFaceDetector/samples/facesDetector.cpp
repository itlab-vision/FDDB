#include <iostream>
#include <cstdlib>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "FacesClassifier.hpp"

using namespace std;
using namespace cv;

int readArguments(int argc, char **argv, string &imgFilename, string &outRectFilename);
void readLfw(const string &filename, const string &origImgDir, vector<Mat> &images);
void readNeg(const string &filename, vector<Mat> &images);

string pathToImages = "/home/artem/projects/itlab/faces/originalPics/";

string helper =
"./source <ImageFilename> <OutputFilename>\n\
\t<ImageFilename> - file name contained source images,\n\
\t<OutputFilename> - file name contained founded face rectangles in the specific format\n\
";

int main(int argc, char** argv)
{
	/*
	string imgsFilename;
    string outFacesFilename;
    if (readArguments(argc, argv, imgsFilename, outFacesFilename) != 0)
    {
        cout << helper << endl;
        return 1;
    }

    //EllipseFileToRectFile(imgsFilename);
    vector<string> imgFilenames;
    ifstream in(imgsFilename.data());
    while (!in.eof())
    {
        string filename;
        in >> filename;
        if (filename.empty())
        {
            break;
        }
        imgFilenames.push_back(filename);
    }
    in.close();

    ofstream out(outFacesFilename.data());
    Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
    Detector detector;
    for (int i = 0; i < imgFilenames.size(); i++)
    {
    	Mat img = imread(pathToImages + imgFilenames[i] + ".jpg", IMREAD_COLOR);
    	
    	vector<Rect> rects;
		vector<float> scores;
		vector<int> labels;
    	detector.Detect(img, labels, scores, rects, classifier, Size(32, 32), 5, 5, 1.2, true);
    	cout << rects.size() << endl;
    	for (int i = 0; i < rects.size(); i++)
		{
			if (labels[i] == 1)
				rectangle(img, rects[i], Scalar(0, 0, 255));
		}
		imshow("asd", img);
    	out << imgFilenames[i] << endl;
        out << rects.size() << endl;
        for (int j = 0; j < rects.size(); j++)
        {
            out << rects[j].x << " " << rects[j].y << " "
                << rects[j].width << " " << rects[j].height << " " << scores[j] << endl;
        }
    }*/
	/*
	Mat img = imread("/imgs/00007.jpg", IMREAD_COLOR);
	Mat img2;
	img.copyTo(img2);

	Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
	
	Detector detector;
	vector<Rect> rects;
	vector<float> scores;
	vector<int> labels;

	detector.Detect(img2, labels, scores, rects, classifier, Size(32, 32), 1, 1, 1.2, false);

	for (int i = 0; i < rects.size(); i++)
	{
		if (labels[i] == 1)
			rectangle(img, rects[i], Scalar(0, 0, 255));
	}
	cout << "Count rectangles = " << rects.size () << endl;
	for (int i = 0; i < rects.size(); i++)
	{
		cout << labels[i] <<  "  ";
	}
	cout << endl;
	imwrite("result.jpg", img);
	*/
	
	vector<Mat> images;
	//readLfw("out.txt", "/imgs/lfw/", images);
	readNeg("/home/artem/projects/itlab/tmp/out.txt", images);
	cout << "reading is done\n";
	Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());

	int faces = 0;
	int notfaces = 0;
	for (int i = 0; i < images.size(); i++)
	{
		Result result = classifier->Classify(images[i]);
		if (result.label == 1)
		{
			faces++;
		}
		else
		{
			notfaces++;
		}
	}

	cout << "Tp Count = " << faces << endl;
	cout << "Fn count = " << notfaces << endl;
	
	waitKey(0);
	return 0;
}

void readNeg(const string &filename, vector<Mat> &images)
{
	ifstream in(filename);
	int i = 0;
	while(!in.eof())
	{
		string filename = "";
		in >> filename;
		Mat img = imread(filename, IMREAD_COLOR);
		if (!img.empty())
			images.push_back(img);
	}

	in.close();
}

void readLfw(const string &filename, const string &origImgDir, vector<Mat> &images)
{
	ifstream in(filename);
	int i = 0;
	while(!in.eof())
	{
		string name = "";
		int count = 0;
		in >> name >> count;
		//cout << name << " " << count << endl;
		//cout << origImgDir + name + "/" + name + "0001.jpg" << endl;
		Mat img = imread(origImgDir + name + "/" + name + "_0001.jpg", IMREAD_COLOR);
		
		if (!img.empty())
		{
			resize(img, img, Size(32, 32));
			images.push_back(img);
		}
		//i++;
		//if (i > 100)
		//	break;
	}

	in.close();
}

int readArguments(int argc, char **argv, string &imgFilename, string &outFacesFilename)
{
    for (int i = 1; i < argc; i++)
    {
        if (imgFilename.empty())
        {
            imgFilename = argv[i];
        }
        else if (outFacesFilename.empty())
        {
            outFacesFilename = argv[i];
        }
        else
        {
            return 1;
        }
    }
    return 0;
}