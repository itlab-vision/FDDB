#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "FacesClassifier.hpp"

 #include <stdio.h>
    #define TIMER_START(name) int64 t_##name = getTickCount()
    #define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
                1000.f * ((getTickCount() - t_##name) / getTickFrequency()))

using namespace std;
using namespace cv;

int readArguments(int argc, char **argv, string &imgFilename, string &outRectFilename);
void readLfw(const string &filename, const string &origImgDir, vector<Mat> &images);
void readNeg(const string &filename, vector<Mat> &images);
void testClassifier(int numClass);
void testDetector(Mat &img, bool fGroupRect = false);
void testDetectorFDDB(const string &imgsFilename, int numFold, const string &outFacesFilename, bool fGroupRect);
void testClassifierFDDB(const string &fliename);
void EllipseToRect(double majorRadius, double minorRadius, double angle, double x, double y, Rect &rect);

string pathToImages = "/home/artem/projects/itlab/faces/originalPics/";
string pathToFolds = "/home/artem/projects/itlab/faces/FDDB-folds/";
string pathToResult = "/home/artem/projects/itlab/faces/torchResult/";

string helper =
"./source <ImageFilename> <OutputFilename>\n\
\t<ImageFilename> - file name contained source images,\n\
\t<OutputFilename> - file name contained founded face rectangles in the specific format\n\
";

int main(int argc, char** argv)
{
	string imgsFilename = "/home/artem/projects/itlab/faces/FDDB-folds/FDDB-fold-01.txt";
    string outFacesFilename = "/home/artem/projects/itlab/faces/torchResult/fold-01-out.txt";

    vector<string> filenamesFolds;
    for (int i = 1; i <= 10; i++)
    {
    	stringstream filename;
    	filename << pathToFolds << "FDDB-fold-";
    	filename.fill('0');
    	filename.width(2);
    	filename << i << ".txt";
    	filenamesFolds.push_back(filename.str());
    }
    vector<string> filenamesResults;
    for (int i = 1; i <= 10; i++)
    {
    	stringstream filename;
    	filename << pathToResult << "fold-";
    	filename.fill('0');
    	filename.width(2);
    	filename << i << "-out.txt";
    	filenamesResults.push_back(filename.str());
    }
    //for (int i = 0; i < 10; i++)
    //{
    //	cout << filenamesResults[i] << endl;
    //}
    //if (readArguments(argc, argv, imgsFilename, outFacesFilename) != 0)
    //{
    //    cout << helper << endl;
    //    return 1;
    //}
    
    //for (int i = 0; i < filenamesFolds.size(); i++)
    //{
    //	testDetectorFDDB(filenamesFolds[i], i + 1, filenamesResults[i], true);
    //}
    
	
	Mat img = imread("/imgs/img_716s.jpg", IMREAD_COLOR);
    TIMER_START(all);
	testDetector(img, false);
	TIMER_END(all);
	
	imwrite("result_back.jpg", img);
	//testClassifierFDDB("/home/artem/projects/itlab/faces/FDDB-folds/FDDB-fold-01-ellipseList.txt");
	//testClassifier(1);
	//waitKey(0);
	return 0;
}

void EllipseToRect(double majorRadius, double minorRadius, double angle, double x, double y, Rect &rect)
{
    RotatedRect rotRect(Point2f(x, y), Size(2.0 * minorRadius, 2.0 * majorRadius), angle);
    rect = rotRect.boundingRect();
}

void testClassifierFDDB(const string &filename)
{
	ifstream in(filename);
	Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
	Detector detector;
	int i = 0;
	while (!in.eof())
    {
        string str;
        in >> str;
        if (str.empty())
        {
            break;
        }

        int count = 0;
        in >> count;

        double majorRadius, minorRadius, angle, x, y;
        int score;
        Mat img = imread(pathToImages + str + ".jpg", IMREAD_COLOR);
        vector<Rect> rightRects;
        for (int i = 0; i < count; i++)
        {
            in >> majorRadius >> minorRadius >> angle >> x >> y >> score;
            Rect rect;
            EllipseToRect(majorRadius, minorRadius, angle, x, y, rect);   
            if (rect.x > 0 && rect.y > 0)
            {
            	rightRects.push_back(rect);
            }
            cout << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;
        }

        Mat faceImg = img(rightRects[0]);
        const double windowSize = 32.0;
        double coef = 0.0;
        if (rightRects[0].height < rightRects[0].width)
          	coef = rightRects[0].height;
        else
           	coef = rightRects[0].width;
        double scale = 32.0 / coef;
        resize(faceImg, faceImg, Size(), scale, scale);
        
        vector<Rect> rects;
		vector<float> scores;
		vector<int> labels;
		bool fGroupRect = true;
		detector.Detect(faceImg, labels, scores, rects, classifier, Size(32, 32), 1, 1, 1.2, 3, fGroupRect);
		cout << faceImg.cols << " " << faceImg.rows << endl;
		for (int i = 0; i < rects.size(); i++)
			rectangle(faceImg, rects[i], Scalar(255, 0, 0));
		cout << str << endl;
		stringstream s;
		s << i;
		imwrite("/home/artem/testClas/" + s.str() + ".jpg", faceImg);
		i++;
		if (i > 30)
			break;
    }
    in.close();
}

void testDetectorFDDB(const string &imgsFilename, int numFold, const string &outFacesFilename, bool fGroupRect)
{
	stringstream numFoldStr;
	numFoldStr << "/home/artem/testClas/fddb/" << numFold << "/";
	string path = numFoldStr.str();

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
    	Mat tmp;
    	img.copyTo(tmp);
    	vector<Rect> rects;
		vector<float> scores;
		vector<int> labels;

		detector.Detect(img, labels, scores, rects, classifier, Size(32, 32), 2, 2, 1.4, 3, fGroupRect);

		out << imgFilenames[i] << endl;
        out << rects.size() << endl;
        for (int j = 0; j < rects.size(); j++)
        {
            out << rects[j].x << " " << rects[j].y << " "
                << rects[j].width << " " << rects[j].height << " " << scores[j] << endl;
        }

        for (int j = 0; j < rects.size(); j++)
		{
			rectangle(tmp, rects[j], Scalar(0, 0, 255));
		}
		stringstream s;
		s << i;
		imwrite(path + s.str() + ".jpg", tmp);
		cout << "It's " << numFold << " fold, image is " << imgFilenames[i] << endl;
		//cout << "/home/artem/testClas/fddb/" + imgFilenames[i] + ".jpg" << endl;
    }
    out.close();
}

void testDetector(Mat &img, bool fGroupRect)
{
	Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
	
	Detector detector;
	vector<Rect> rects;
	vector<float> scores;
	vector<int> labels;

	//resize(img, img, Size((int)(img.cols / 7.8125), (int)(img.rows / 7.8125)), 0, 0, INTER_LINEAR);
	//cout << img.cols << " " << img.rows << endl;
	detector.Detect(img, labels, scores, rects, classifier, Size(32, 32), 1, 1, 1.2, 3, fGroupRect);

	for (int i = 0; i < rects.size(); i++)
	{
		rectangle(img, rects[i], Scalar(0, 0, 255));
	}
	cout << "Faces count = " << rects.size () << endl;
}

void testClassifier(int numClass)
{
	vector<Mat> images;
	if (numClass == 1)
		readLfw("/imgs/lfw-names.txt", "/imgs/pos/", images);
	else if (numClass == 2)
		readNeg("/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/imgs/neg.txt", images);
	cout << "reading is done\n";
	Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());

	int error = 0;
	for (int i = 0; i < images.size(); i++)
	{
		Result result = classifier->Classify(images[i]);
		if (result.label != numClass)
		{
			error++;
			stringstream s;
			s << i;	
			imwrite("/home/artem/testClas/errorNeg/" + s.str() + ".jpg", images[i]);
		}
	}
	cout << "Tp count = " << images.size() - error << endl;
	cout << "Fp count = " << error << endl;
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
		for (int i = 0; i < count; i++)
		{
			stringstream ss;
			ss.width(4);
			ss.fill('0');
			ss << i + 1;
	
			Mat img = imread(origImgDir + name + "/" + name + "_" + ss.str() + ".jpg", IMREAD_COLOR);
			if (!img.empty())
			{
				resize(img, img, Size(32, 32));
				images.push_back(img);
			}
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