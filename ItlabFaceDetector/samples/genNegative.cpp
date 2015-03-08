#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "FacesClassifier.hpp"

#include <omp.h>

using namespace std;
using namespace cv;

string pathToImages = "/home/artem/projects/itlab/datasets/lfw/";
string pathToResultImages = "/home/artem/projects/itlab/negatives/neg_lfw/";

int readArguments(int argc, char **argv, string &annotsFilename);
void readAnnotationFile(const string &filename, string &imgFilename, vector<Rect> &objRect, vector<string> &objClass);

//image_name face_bbox_x face_bbox_y face_bbox_width face_bbox_height headpose num_facial_features left_eye_left_x 
//left_eye_left_y left_eye_right_x left_eye_right_y mouth_left_x mouth_left_y mouth_right_x mouth_right_y outer_lower_lib_x outer_lower_lib_y outer_upper_lib_x outer_upper_lib_y right_eye_left_x right_eye_left_y right_eye_right_x right_eye_right_y nose_left_x nose_left_y nose_right_x nose_right_y

int main(int argc, char **argv)
{
	string annotsFilename;
	if (readArguments(argc, argv, annotsFilename) != 0)
    {
        return 1;
    }
    annotsFilename = "/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/imgs/lfw_ffd_ann.txt";
	ifstream in(annotsFilename);
	vector<string> annotsFilenames;
    vector<Rect> faces;
	while (!in.eof())
    {
        string filename;
        
        Rect face;
        int headpose, numFacialFeatures;
        in >> filename;
        if (filename.empty())
        {
            break;
        }
        in >> face.x >> face.y >> face.width >> face.height;
        int tmp;
        for (int i = 0; i < 22; i++)
            in >> tmp;

        annotsFilenames.push_back(filename);
        faces.push_back(face);
    }
    in.close();
    //cout << annotsFilenames.size() << flush;

    cout << faces.size() << endl;

    for (uint i = 1; i < annotsFilenames.size(); i++)
    {
        cout << pathToImages + annotsFilenames[i] << flush << endl;
        Mat img = imread(pathToImages + annotsFilenames[i], IMREAD_COLOR);

        vector<Rect> rects;
        vector<double> scores;
        vector<int> labels;
        vector<Rect> negatives;

        Ptr<Classifier> classifier = Ptr<Classifier>(new FacesClassifier());
        Detector detector;
        detector.Detect(img, labels, scores, rects, classifier, Size(32, 32), 1, 1, 1.2, 3, true);

        for (uint j = 0; j < rects.size(); j++)
        {
            Rect intersecRect = faces[i] & rects[j];
            Rect unionRect = faces[i] | rects[j];

            double coef = (double)intersecRect.area() / (double)unionRect.area();
            //cout << coef << endl;
            if (coef < 0.3)
            {
                negatives.push_back(rects[j]);
            }
        }

        for (uint j = 0; j < negatives.size(); j++)
        {
            //rectangle(img, negatives[j], Scalar(0, 0, 255));
            stringstream path;
            path << i << "_" << j << ".jpg";
            Mat neg = img(negatives[j]);
            resize(neg, neg, Size(32, 32), 0, 0, INTER_LINEAR);
            imwrite(pathToResultImages + path.str(), neg);
        }

        //imshow(pathToResultImages + annotsFilenames[i], img);
        cout << i << endl;
    }

    waitKey(0);
	return 0;
}

int readArguments(int argc, char **argv, string &annotsFilename)
{
    for (int i = 1; i < argc; i++)
    {
        if (annotsFilename.empty())
        {
            annotsFilename = argv[i];
        }
        else
        {
            return 1;
        }
    }
    return 0;
}