#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Detector.hpp"
#include "FacesClassifier.hpp"

#include "rapidXml/rapidxml.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

using namespace std;
using namespace cv;
using namespace rapidxml;

string pathToAnnotation = "/home/artem/projects/itlab/negatives/0_db/VOCdevkit/VOC2007/Annotations/";
string pathToImages = "/home/artem/projects/itlab/negatives/0_db/VOCdevkit/VOC2007/JPEGImages/";
string pathToResultImages = "/home/artem/projects/itlab/negatives/";

int readArguments(int argc, char **argv, string &annotsFilename);
void readAnnotationFile(const string &filename, string &imgFilename, vector<Rect> &objRect, vector<string> &objClass);
void getListFiles(string &path);
int getdir (string dir, vector<string> &files);
void getBackImg(Mat &img, const vector<Rect> &objRects, vector<Mat> &backImgs);

int main(int argc, char **argv)
{
	string annotsFilename;
	if (readArguments(argc, argv, annotsFilename) != 0)
    {
        return 1;
    }
    /*annotsFilename = "/home/artem/projects/itlab/negatives/0_db/VOCdevkit/VOC2007/annots.txt";
	ifstream in(annotsFilename);
	vector<string> annotsFilenames;
	while (!in.eof())
    {
        string filename;
        in >> filename;
        if (filename.empty())
        {
            break;
        }
        annotsFilenames.push_back(filename);
    }
    in.close();*/
    /*
    vector<string> annotsFilenames;
    getdir(pathToAnnotation, annotsFilenames);
    for (int i = 0; i < 40; i++)
    	cout << annotsFilenames[i] << endl;
    */
    /*
    vector<string> annotsFilenames;
    if ( !getdir(pathToAnnotation, annotsFilenames) )
    {
    	for (int i = 2; i < annotsFilenames.size(); i++)
    	{
    		string annotFilename = pathToAnnotation + annotsFilenames[i];
    		string imgFilename;
    		vector<Rect> objRect;
    		vector<string> objClass;

    		readAnnotationFile(annotFilename, imgFilename, objRect, objClass);
    		Mat img = imread(pathToImages + imgFilename, IMREAD_COLOR);
    		
    		for (int j = 0; j < objRect.size(); j++)
    		{
    			Mat objImg = img(objRect[j]);
    			const double windowSize = 32.0;
        		double coef = 0.0;
        		if (objRect[j].height < objRect[j].width)
        		  	coef = objRect[j].height;
        		else
        		   	coef = objRect[j].width;
        		double scale = windowSize / coef;
        		resize(objImg, objImg, Size(), scale, scale);
        		objImg = objImg( Rect(0, 0, (int)windowSize, (int)windowSize) );

    	    	int pos = imgFilename.find(".jpg");
    	    	string name = imgFilename.substr(0, pos);
    	    	stringstream ss;
    	    	ss << pathToResultImages << objClass[j] << "/" << name << "_" << j << ".jpg";
    	    	imwrite(ss.str(), objImg);
    		}
    		
    		vector<Mat> backImgs;
    		getBackImg(img, objRect, backImgs);
    		for (int j = 0; j < backImgs.size(); j++)
    		{
    			int pos = imgFilename.find(".jpg");
    	    	string name = imgFilename.substr(0, pos);
    	    	stringstream ss;
    	    	ss << pathToResultImages << "background/" << name << "_" << j << ".jpg";

    			imwrite(ss.str(), backImgs[j]);
    		}
    		cout << i << endl;
    	}
    }
    */
    
	return 0;
}

void getBackImg(Mat &img, const vector<Rect> &objRects, vector<Mat> &backImgs)
{
	const int windowSize = 128;
	int dx = 128, dy = 128;
	backImgs.clear();
	
	for (int y = 0; y < img.rows - windowSize + 1; y += dy)
    {
        for (int x = 0; x < img.cols - windowSize + 1; x += dx)
        {
            Rect rect(x, y, windowSize, windowSize);
            bool flag = false;
            for (uint i = 0; i < objRects.size(); i++)
            {
            	Rect intersecRect = rect & objRects[i];
            	if (intersecRect.width != 0 || intersecRect.height != 0)
            	{
            		flag = true;
            		break;
            	}
            }
            if (!flag)
            {
            	Mat backImg = img(rect);
            	resize(backImg, backImg, Size(32, 32), 0, 0);
            	backImgs.push_back(backImg);
            }
        }
    }
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void readAnnotationFile(const string &filename, string &imgFilename, vector<Rect> &objRects, vector<string> &objClass)
{
	ifstream inAnnot(filename);
    stringstream strStream;
	strStream << inAnnot.rdbuf();//read the file
	string str = strStream.str();//str holds the content of the file

    xml_document<> doc;    // character type defaults to char
    char *text = new char[str.size() + 1];
    strcpy (text, str.c_str());
	doc.parse<0>(text);

	Size imgSize;;
	for (xml_node<> *node =  doc.first_node()->first_node(); node; node = node->next_sibling())
	{
		string nodeName(node->name());
		if (nodeName.find("filename") != string::npos)
		{
			imgFilename = node->value();
		}
		else if (nodeName.find("size") != string::npos)
		{
			xml_node<> *nodeSize = node->first_node();
			imgSize.width = atoi(nodeSize->value());
			nodeSize = nodeSize->next_sibling();
			imgSize.height = atoi(nodeSize->value());
		}
		else if (nodeName.find("object") != string::npos)
		{
			for (xml_node<> *nodeObj =  node->first_node(); nodeObj; nodeObj = nodeObj->next_sibling())
			{
				string nodeObjName = nodeObj->name();
				if (nodeObjName.find("name") != string::npos)
				{
					objClass.push_back(nodeObj->value()); 
				}
				else if (nodeObjName.find("bndbox") != string::npos)
				{
					int xmin, ymin, xmax, ymax;
					xml_node<> *nodeRect = nodeObj->first_node();
					xmin = atoi(nodeRect->value());
					nodeRect = nodeRect->next_sibling();
					ymin = atoi(nodeRect->value());
					nodeRect = nodeRect->next_sibling();
					xmax = atoi(nodeRect->value());
					nodeRect = nodeRect->next_sibling();
					ymax = atoi(nodeRect->value());

					objRects.push_back(Rect(xmin, ymin, xmax - xmin, ymax - ymin));
				}
			} 
		}
	}
	delete[] text;
	inAnnot.close();
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