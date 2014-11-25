#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <iostream>
#include "list"

#include </home/kate/opencv/include/opencv2/opencv.hpp>

#include "FaceClassif.h"
using namespace cv;
using namespace std;

class ClassifName : public FaceClassifier
{
   public:
    int Classify(Mat m)
    {
        return rand()%2;
    }
};

#endif // CLASSIFY_H
