// #include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
    Mat image = imread("lena.jpg");
    Mat logo = imread("dataguru_logo.jpg");
    Mat ROIimage = image(cv::Rect(385,270,logo.cols,logo.rows));
    //Mat mask = imread("F:\\VS2010workplace\\cvTestLoge\\cvTestLoge\\logo.bmp",0);
    //logo.copyTo(ROIimage,mask);
    addWeighted(ROIimage,1.0,logo,0.7,0,ROIimage);
    namedWindow("logo");
    imshow("logo",image);
    waitKey(0);
    return 0;
}
