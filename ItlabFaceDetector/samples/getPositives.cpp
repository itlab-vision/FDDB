#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

string pathToImages = "/home/artem/projects/itlab/datasets/lfw/";
string pathToResultImages = "/home/artem/projects/itlab/positives/";

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
    vector<Rect> leftEyes;
    vector<Rect> mouthes;
    vector<Rect> outers;
    vector<Rect> rightEyes;
    vector<Rect> noses;
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
        in >> headpose >> numFacialFeatures;

        int x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;
        Rect leftEye(Point(x1, y1), Point(x2, y2));

        in >> x1 >> y1 >> x2 >> y2;
        Rect mouth(Point(x1, y1), Point(x2, y2));

        in >> x1 >> y1 >> x2 >> y2;
        Rect outer(Point(x1, y1), Point(x2, y2));

        in >> x1 >> y1 >> x2 >> y2;
        Rect rightEye(Point(x1, y1), Point(x2, y2));

        in >> x1 >> y1 >> x2 >> y2;
        Rect nose(Point(x1, y1), Point(x2, y2));

        annotsFilenames.push_back(filename);
        noses.push_back(nose);
        leftEyes.push_back(leftEye);
        mouthes.push_back(mouth);
        outers.push_back(outer);
        rightEyes.push_back(rightEye);
        faces.push_back(face);
    }
    in.close();
    //cout << annotsFilenames.size() << flush;
    /*for (int i = 0; i < annotsFilenames.size(); i++)
    {
        cout << pathToImages + annotsFilenames[i] << flush << endl;
        Mat img = imread(pathToImages + annotsFilenames[i], IMREAD_COLOR);

        Mat face = img(faces[i]);
        resize(face, face, Size(32, 32), 0, 0, INTER_LINEAR);
        imwrite(pathToResultImages + annotsFilenames[i], face);
        cout << i << endl;
    }*/
    for (int i = 0; i < 1/*annotsFilenames.size()*/; i++)
    {
        cout << pathToImages + annotsFilenames[i] << flush << endl;
        Mat img = imread(pathToImages + annotsFilenames[i], IMREAD_COLOR);
        Mat face = img(faces[i]);
        //cout << faces[i].x << " " << faces[i].width << endl;
        //rectangle(img, faces[i], Scalar(255, 0, 0));
        rectangle(face, leftEyes[i], Scalar(255, 0, 0));
        rectangle(face, rightEyes[i], Scalar(255, 0, 0));
        rectangle(face, mouthes[i], Scalar(255, 0, 0));
        rectangle(face, outers[i], Scalar(255, 0, 0));
        rectangle(face, noses[i], Scalar(255, 0, 0));
        imshow(pathToResultImages + annotsFilenames[i], face);
        cout << i << endl;
    }
    
    /*for (int i = 0; i < annotsFilenames.size(); i++)
    {
        //cout << pathToImages + annotsFilenames[i] << flush << endl;
        Mat img = imread(pathToImages + annotsFilenames[i], IMREAD_COLOR);
        if (img.cols != 32 || img.rows != 32)
        {
            cout << annotsFilenames[i] << endl;
        }
    }*/
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