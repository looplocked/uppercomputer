#pragma once
#include <vector>
#include <iostream>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
#include "OpenNI.h" 

typedef std::vector<std::pair<double, int> > sortType;

using namespace std;
using namespace cv;
using namespace openni;


bool findPrimaryAngle(std::vector<cv::Vec4f>& lines);
bool selectPoints(std::vector<cv::Point>& Points);
bool SortFaster(sortType& dists, int Top_num);
void CheckOpenNIError(Status result, string status);