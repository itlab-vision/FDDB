#ifndef FACECLASSIF_H
#define FACECLASSIF_H

#include </home/kate/opencv/include/opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;
class FaceClassifier
{
public :
    virtual int Classify(Mat m) = 0;
};


#endif // FACECLASSIF_H
