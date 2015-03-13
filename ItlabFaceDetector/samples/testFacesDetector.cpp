#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <omp.h>

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

int readArguments(int argc, char **argv, vector<string> &filenames, string &resultDir, string &resultImgsDir, 
                  string &mode, int &step, double &scale, int &minNeighbours, bool &groupRect);

void detectListImages(vector<string> &filenames, Ptr<Classifier> classifier, int step, double scale, int minNeighbours, 
                      bool groupRect, string &resultDir, string &resultImgsDir, string &resultFilename);

void EllipseToRect(double majorRadius, double minorRadius, double angle, double x, double y, Rect &rect);


string helper =
"./testFacesDetector -i <Img1> .. <ImgN>  -r <resultDir> -s <resultImgDir> \n\
\t<ImageFilename> - file name contained source images,\n\
\t<OutputFilename> - file name contained founded face rectangles in the specific format\n\
";

int countProccesedImgs = 0;

int main(int argc, char** argv)
{
    vector<string> filenames;
    string mode, resultDir, resultImgsDir;
    int step = 1, minNeighbours = 3;
    double scale = 1.2;
    bool groupRect = false;
    if (readArguments(argc, argv, filenames, resultDir, resultImgsDir, mode, step, scale, minNeighbours, groupRect))
    {
        cout << helper << endl;
        return 1;
    }
    
    Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
    if (mode.compare("-i") == 0)
    {
        string resultFilename = "result.txt";
        detectListImages(filenames, classifier, step, scale, minNeighbours, 
                         groupRect, resultDir, resultImgsDir, resultFilename);
    }
    else if (mode.compare("-f") == 0)
    {
        for (uint i = 0; i < filenames.size(); i++)
        {
            vector<string> imgFilenames;
            ifstream in(filenames[i]);
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

            int startPos = filenames[i].find_last_of("/") + 1;
            int endPos = filenames[i].find(".");
            stringstream resultFilenameSS;
            resultFilenameSS << filenames[i].substr(startPos, endPos - startPos) << "-out.txt";
            string resultFilename = resultFilenameSS.str();

            detectListImages(imgFilenames, classifier, step, scale, minNeighbours, 
                             groupRect, resultDir, resultImgsDir, resultFilename);
        }
    }
    else if (mode.compare("-fddb") == 0)
    {
        vector<string> filenamesFolds;
        for (uint i = 1; i <= 10; i++)
        {
            stringstream filename;
            filename << filenames[0] << "FDDB-fold-";
            filename.fill('0');
            filename.width(2);
            filename << i << ".txt";
            filenamesFolds.push_back(filename.str());
        }

        vector<string> filenamesResults;
        for (uint i = 1; i <= 10; i++)
        {
            stringstream filename;
            filename << "fold-";
            filename.fill('0');
            filename.width(2);
            filename << i << "-out.txt";
            filenamesResults.push_back(filename.str());
        }
        
        for (uint i = 0; i < filenamesFolds.size(); i++)
        {
            vector<string> imgFilenames;
            ifstream in(filenamesFolds[i]);
            while (!in.eof())
            {
                string filename;
                in >> filename;
                if (filename.empty())
                {
                    break;
                }
                imgFilenames.push_back(filenames[1] + filename + ".jpg");
            }
            in.close();
            detectListImages(imgFilenames, classifier, step, scale, minNeighbours, 
                             groupRect, resultDir, resultImgsDir, filenamesResults[i]);
        }
    }

	return 0;
}

void detectListImages(vector<string> &filenames, Ptr<Classifier> classifier, int step, double scale, 
                      int minNeighbours, bool groupRect, string &resultDir, string &resultImgsDir, 
                      string &resultFilename)
{    
    ofstream out;
    if (resultDir.compare("") != 0)
    {
        out.open(resultDir + resultFilename, ofstream::out);
        cout << resultDir + resultFilename << endl;
    }

    vector<int> labels;
    vector<Rect> rects;
    vector<double> scores;
    #pragma omp parallel for //shared(countProccesedImgs)
    for (uint i = 0; i < filenames.size(); i++)
    {
        Detector detector;
        Ptr<Classifier> classifier1 = Ptr<Classifier>(new FacesClassifier());
        Mat img = imread(filenames[i], IMREAD_COLOR);

        cout << filenames[i] << " is now proccessed" << endl;

        detector.Detect(img, labels, scores, rects, classifier1, Size(32, 32), step, step, scale, minNeighbours, groupRect);

        if (out.is_open())
        {
            out << filenames[i] << endl;
            out << rects.size() << endl;
            for (uint j = 0; j < rects.size(); j++)
            {
                out << rects[j].x << " " << rects[j].y << " ";
                out << rects[j].width << " " << rects[j].height << " " << scores[j] << endl;
            }
        }
        if (resultImgsDir.compare("") != 0)
        {
            for (uint j = 0; j < rects.size(); j++)
            {
                rectangle(img, rects[j], Scalar(0, 0, 255));
            }

            int startPos = filenames[i].find_last_of("/") + 1;
            int endPos = filenames[i].find(".");
            stringstream resultFilename;
            resultFilename << filenames[i].substr(startPos, endPos - startPos) << "_" << time(NULL) << ".jpg";
            imwrite(resultImgsDir + resultFilename.str(), img);
        }

        //countProccesedImgs++;
        //cout << countProccesedImgs << " from 2845" << endl;//?
    }

    out.close();
}


int readArguments(int argc, char **argv, vector<string> &filenames, string &resultDir, string &resultImgsDir, 
                  string &mode, int &step, double &scale, int &minNeighbours, bool &groupRect)
{
    string curTypeParam;
    for (int i = 1; i < argc; i++)
    {
        string param(argv[i]);
        if (param.compare("-i") == 0)
        {
            curTypeParam = param;
            mode = param;
        }
        else if (param.compare("-f") == 0)
        {
            curTypeParam = param;
            mode = param;
        }
        else if (param.compare("-r") == 0)
        {
            curTypeParam = param;
        }
        else if (param.compare("-s") == 0)
        {
            curTypeParam = param;
        }
        else if (param.compare("--scale") == 0)
        {
            curTypeParam = param;
        }
        else if (param.compare("--step") == 0)
        {
            curTypeParam = param;
        }
        else if (param.compare("--grouping") == 0)
        {
            curTypeParam = param;
        }
        else if (param.compare("-fddb") == 0)
        {
            curTypeParam = param;
            mode = param;
        }
        else
        {
            if (curTypeParam.compare("-i") == 0 || curTypeParam.compare("-f") == 0
                || curTypeParam.compare("-fddb") == 0)
            {
                filenames.push_back(param);
            }
            else if (curTypeParam.compare("-r") == 0)
            {
                resultDir = param;
            }
            else if (curTypeParam.compare("-s") == 0)
            {
                resultImgsDir = param;
            }
            else if (curTypeParam.compare("--scale") == 0)
            {
                scale = atof(param.c_str());
            }
            else if (curTypeParam.compare("--step") == 0)
            {
                step = atoi(param.c_str());
            }
            else if (curTypeParam.compare("--grouping") == 0)
            {
                groupRect = (bool)atoi(param.c_str());
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

void EllipseToRect(double majorRadius, double minorRadius, double angle, double x, double y, Rect &rect)
{
    RotatedRect rotRect(Point2f(x, y), Size(2.0 * minorRadius, 2.0 * majorRadius), angle);
    rect = rotRect.boundingRect();
}