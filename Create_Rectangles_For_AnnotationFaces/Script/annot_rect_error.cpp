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



using namespace cv;

using namespace std;

vector<string> split(const string& s, const string& delim, const bool keep_empty = true)
{
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }

    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}

void main()
{
	
	ifstream files("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/updata_annatation.txt");
	ofstream new_file("D:/my-study/OpenCV/DataSet/DataSet_for_train_Faces_Detector/PositiveImage/new_new_new.txt"); 
	char s[1000];
	Mat image;
	int c = 0;
	std::vector<string> mass;

	while (files.getline(s,1000))
	{
		c++;
		string str(s);
		mass = split(str," ");
	  
		image = imread( "D:/my-study/OpenCV/DataSet/"+mass[0],CV_LOAD_IMAGE_COLOR);
		new_file<<mass[0]<< " ";
		new_file<<mass[1]<< " ";
		for (int i=0;i< atoi( mass[1].c_str() ); i++)
		{
			if (atoi( mass[i*4 + 2].c_str() ) <0)
				mass[i*4 + 2]="0";
			if (atoi( mass[i*4 + 3].c_str() ) <0)
				mass[i*4 + 3]="0";
			if (atoi( mass[i*4 + 4].c_str() ) <0)
			{
				cout<<s<<endl;
			}
			if (atoi( mass[i*4 + 5].c_str() ) <0)
			{
				cout<<s<<endl;
			}
			if (atoi( mass[i*4 + 2].c_str() )  + atoi( mass[i*4 + 4].c_str() )> image.cols)
				mass[i*4 + 4]= to_string( image.cols - atoi( mass[i*4 + 2].c_str() ) -2 );
			if (atoi( mass[i*4 + 3].c_str() )  + atoi( mass[i*4 + 5].c_str() )> image.rows)
				if ( mass[i*4 + 3]=="0")
				{
					mass[i*4 + 5]=to_string( image.rows -1);
				}
				else
				{
					mass[i*4 + 5]= to_string( image.rows - atoi( mass[i*4 + 3].c_str() ) -2 );
				}

			new_file<< mass[i*4 + 2]<< " " << mass[i*4 + 3]<<" " << mass[i*4 + 4] << " "<< mass[i*4 + 5] << " ";
			rectangle(image,Point( atoi(mass[i*4 + 2].c_str()),atoi(mass[i*4 + 3].c_str())),
				Point (atoi(mass[i*4 + 2].c_str()) + atoi(mass[i*4 + 4].c_str()  ), atoi(mass[i*4 + 3].c_str()) + atoi(mass[i*4 + 5].c_str())   ),COLOR_BayerBG2BGR);
		}
		new_file<<"\n";
		
		mass = split(mass[0],"/");
		imwrite("RectImageSample/" + mass[mass.size() -1], image);


	}
}
