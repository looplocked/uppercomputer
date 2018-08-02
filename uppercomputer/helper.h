#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
#include "LineSegmentDetector.h"
#include "OpenNI.h" 

#define HAVE_OPENCV

#ifdef HAVE_OPENCV
#include <opencv2/flann.hpp>
#endif

typedef std::vector<std::pair<double, int> > sortType;

using namespace std;
using namespace cv;
using namespace openni;

void printLog(string log);
void deleteLog();
string MatToStr(Mat m);

#endif