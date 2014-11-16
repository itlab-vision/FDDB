#ifndef FACEDETEC_H
#define FACEDETEC_H
#include <iostream>
#include "list"

#include </home/kate/opencv/include/opencv2/opencv.hpp>

#include "Classify.h"
using namespace cv;
using namespace std;

class FacesDetector
{
  private:
    ClassifName classifier;

public:
    void Detect(Mat image,vector<Rect> &rect, Size min_s, Size max_s, int step)  //step to x = step to y
    {

        int count = 0;
        rect.clear();

        Mat slidImage;

        Rect detectRect;

        int sizeWindosX = min_s.width;
        int sizeWindosY = min_s.height;

        int maxSizeWindowsX = max_s.width;
        int maxSizeWindowsY = max_s.height;

        int j=0;
        int k = 0;

        while ( (sizeWindosX <= maxSizeWindowsX ) and (sizeWindosY <=maxSizeWindowsY ) )
        {

            slidImage.create(min_s,CV_8UC1);

            if (j+sizeWindosX <= image.cols)
            {
                slidImage =  image(Range(k,k+sizeWindosY),Range(j,j+sizeWindosX));

                int answer = classifier.Classify(slidImage);

                if (answer==1)
                {

                    detectRect.x= j;
                    detectRect.y = k;
                    detectRect.width  = sizeWindosX;
                    detectRect.height = sizeWindosY;
                    rect.push_back(detectRect);
                }

                count++;
                cout<<count<<endl;
                j+=step;
            }
            else
            {
                j=0;
                if (k+step +sizeWindosY <= image.rows)
                    k+=step;
                else
                {
                    //прошлись по всему изображению
                    //можно начать маштабировать окно
                    sizeWindosX = min_s.width + 1;
                    sizeWindosY = min_s.height + 1;
                    min_s = Size(sizeWindosX,sizeWindosY);
                    j=0;
                    k=0;
                }
            }

        }
        for (int i=0;i<rect.size();i++)
        {

            detectRect = rect[i];
            rectangle(image,Point(detectRect.x,detectRect.y),Point(detectRect.width,detectRect.height),COLOR_BayerBG2BGR);

        }

       }
};

#endif // FACEDETEC_H
