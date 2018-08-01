#pragma once
#ifndef ROBOTINITIALIZATION_H
#define ROBOTINITIALIZATION_H

#include <QtCore>
#include <QDebug>
#include "opencv2/core/core.hpp" 
#include "RobotControl.h"
#include "Camera.h"
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
	void extractFeature();

signals:
	void initReady(Mat initjacob, Mat initpose, Mat feature, Mat giventarget);

signals:
	void getFeature();

signals:
	void moveNextStep();

private:
	RobotControl* robot;
	Camera* camera;
	int count = 0;
	Mat prePose;
	Mat preFeature;
	Mat jacobian;
	Mat DF;
	Mat theta;
	Mat target;
};


#endif

