#pragma once
#ifndef ROBOTINITIALIZATION_H
#define ROBOTINITIALIZATION_H

#include <QtCore>
#include <QDebug>
#include <QTimer>
#include "opencv2/core/core.hpp" 
#include "RobotControl.h"
#include "cameradisplay.h"
#include "helper.h"

using namespace std;
using namespace cv;

class RobotInitialization : public QObject{
	Q_OBJECT
public:
	RobotInitialization(QObject * parent = 0);
	Mat getJacobian();
	~RobotInitialization();

public slots:
	void startInitialize();
	void moveAndRecord();

signals:
	void initReady(Mat initjacob, Mat initpose, Mat feature, Mat giventarget);

private:
	RobotControl* robot;
	CameraDisplay* camera;
	QTimer *timer;
	int count = 0;
	Mat prePose = Mat(6, 1, CV_64FC1);
	Mat preFeature = Mat(8, 1, CV_64FC1);
	Mat jacobian = Mat(8, 6, CV_64FC1);
	Mat DF = Mat(8, 6, CV_64FC1);
	Mat theta = Mat(6, 6, CV_64FC1);
	Mat target = Mat(8, 1, CV_64FC1);
};


#endif

