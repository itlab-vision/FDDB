
#include "stdafx.h"
#include <fstream> 

#include "opencv2\opencv.hpp"
 #include "opencv2\objdetect\objdetect.hpp"
 #include "opencv2\highgui\highgui.hpp"
 #include "opencv2\imgproc\imgproc.hpp"

#include <iostream>
#include "conio.h"
#include "math.h"
#include "time.h"

//#include <sstream>

using namespace cv;

using namespace std;

CascadeClassifier facedetector;

void main(int argc, _TCHAR* argv[])
{
	ifstream files("FDDB-folds/FDDB-fold-10.txt");
	ifstream grountTrueFile;

	ofstream new_file("GroupRect/fold-10-out.txt"); 

	char s[100];
	std::vector<int>  rejectLevels;
	std::vector<double> levelWeights;
	std::vector<int> weight;

	int CoefK=1000;
	double score;
	double eps=0;
	if (!facedetector.load("lbpcascade_frontalface.xml"))
	{
		cout<<"error load"<<endl;
	}
	std::vector<Rect> faces;
	Mat frame_gray;
	Mat frame;
	int count=0;

	int count_face;
	char str_cascade[100];
	double start_time = clock();
	while (files.getline(s,100))
	{
		if (s!="")
		{
			try
			{
				
				frame = imread((string)s+".jpg",CV_LOAD_IMAGE_COLOR);

				cvtColor( frame, frame_gray,CV_BGR2GRAY);

				facedetector.detectMultiScale(frame_gray,faces,rejectLevels,levelWeights,1.2,0,0,Size(),Size(),true);

				//groupRectangles(faces,rejectLevels,levelWeights, 1 ,0.2);

				new_file<< s <<endl;
				new_file<<faces.size() <<endl;
				string name = "datectFace" + (string)s;

				for( int i = 0; i < faces.size(); i++ )
				{
					rectangle(frame,Point(faces[i].x,faces[i].y),Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height ),COLOR_BGRA2BGR);

					score = CoefK*rejectLevels[i] + levelWeights[i];


					new_file<<faces[i].x << " "<<faces[i].y<< " "<<faces[i].width<< " "<<faces[i].height<<" "<<score;
					new_file<<endl;

				}
								
				name = "resultDatectFaces/"+name.erase(0,25);
				cout<<count<<" .) DetectFace "<< faces.size()<<" and save in : "<<name<<endl;
				count++;
				//imwrite(name+".jpg",frame);

			}
			catch(...)
			{
				break;
			}
		}
	}
	double finish_time = clock();
	cout<<"time  =  "<<(finish_time - start_time)/1000.0<<endl;
	new_file.close();
	_getch();

}