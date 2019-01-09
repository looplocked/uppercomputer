#pragma once
#ifndef VISUALSERVO_H
#define VISUALSERVO_H

#define COMPENSATION 0.1
#define LAMBDA 0.1
#define cube 1

#include "opencv2/core/core.hpp" 
#include "RobotControl.h"
#include "Camera.h"

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace cv;

class VisualServo
{
public:
	VisualServo();
	~VisualServo();

	void initial();
	void RobotInitial();
	void servo();
private:
	Camera *camera;
	RobotControl *robot;
	Mat theta;
	Mat DF;
	int count;

	Mat prePose;
	Mat pose;
	Mat preFeature;
	Mat feature;
	Mat preJacob;
	Mat jacob;
	Mat prerls;
	Mat rls;
	Mat target;

	string matToStr(Mat m);
	void printLog(string log);

	mutex count_mtx;
	condition_variable init_ready;
};


#endif