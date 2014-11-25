#include <iostream>
#include "wait.h"
#include <stdlib.h>

#include </home/kate/opencv/include/opencv2/opencv.hpp>

#include "FaceDetec.h"
#include "FaceClassif.h"
using namespace cv;
using namespace std;

int main()
{

   FacesDetector *detector;
    Mat image = imread("/home/kate/OriginPic/2002/07/19/big/img_18.jpg",IMREAD_COLOR);
    /*
     * Минимальный и максимальный размер окна должны быть пропорциональны по длинне и ширине
     */
    vector<Rect> rect;
    detector->Detect(image,rect,Size(24,24),Size(100,100),3);

    cout<<" cout detection faces "<<rect.size()<<endl;
    cout<<" exit"<<endl;
    return 0;
}

