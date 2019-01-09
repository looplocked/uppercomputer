#pragma once
#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#define DATA_LENGTH 1108
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define PI 3.14159265
#define STEPSIZE 0.005

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <thread>
#include <mutex>

#include "opencv2/core/core.hpp" 
#include "error.h"

using std::vector;
using std::string;
using std::cout;
using std::deque;
using std::endl;
using std::to_string;
using std::stringstream;
using std::ofstream;
using std::thread;
using std::mutex;

using namespace cv;


class RobotControl
{
public:
	RobotControl();
	~RobotControl();
	void initial();
	vector<double> getJointAngle();
	void movej(vector<double>& pose, double speed=1.05, double a=1.4);
	void servoj(vector<double>& pose);
	void Stop();
	bool isReachedJ(vector<double>& target, double threshold);
	void deadServo(double t = 0.008, double lookahead_time = 0.1, double gain = 300);
	void deleteLog();
	void printLog(string);

private:
	string doubleToString(double input);
	string intToString(int input);
	void poseReadThread();
	void safetyCheck(vector<double>& pose);
	
	void close();

	vector<double> globalPose;
	deque<vector<double>> poseQueue;
	mutex queue_mtx;
	mutex mtx;
	
	SOCKET socketClient;
	sockaddr_in addrSrv;
};


#endif