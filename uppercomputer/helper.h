#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
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


bool findPrimaryAngle(std::vector<cv::Vec4f>& lines);
bool selectPoints(std::vector<cv::Point>& Points);
bool SortFaster(sortType& dists, int Top_num);
void CheckOpenNIError(Status result, string status);
Mat processAndGetFeature(Mat originimg, vector<Point>& Points);
Mat mirrorMap(Mat srcimg);

#endif