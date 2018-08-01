#pragma once
#ifndef CAMERA_H    //预编译头很重要
#define CAMERA_H    //不加会编译失败


#include <stdlib.h>  
#include <iostream>  
#include <string> 
#include <thread>
#include <mutex>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
#include "LineSegmentDetector.h"
#include <opencv2/flann.hpp>
#include "helper.h"
#include <Windows.h>

typedef std::vector<std::pair<double, int> > sortType;

using namespace std;

class Camera
{
public:
	Camera();
	~Camera();
	void initial();
	cv::Mat getOriginImg();
	cv::Mat getFeatureImg();
	vector<double> getFeaturePoints();

private:
	cv::Point init_point;
	mutex ori_mutex;
	mutex fea_mutex;
	mutex point_mutex;

	cv::Mat origin_img;
	cv::Mat feature_img;
	vector<double> feature_point;

	cv::VideoCapture m_capture;
	void imageProcessThread();

	bool needReverse(cv::Vec4f line1, cv::Vec4f line2);
	void enableClockWise(std::vector<cv::Point>& Points);
	void transPoints(std::vector<cv::Point>& Points, int index);
	vector<double> flatPoints(vector<cv::Point>& points);
	bool findPrimaryAngle(std::vector<cv::Vec4f>& lines);
	bool selectPoints(std::vector<cv::Point>& Points);
	bool SortFaster(sortType& dists, int Top_num);
	cv::Mat mirrorMap(cv::Mat srcimg);

	void printLog(string log);
	void deleteLog();
};

#endif
