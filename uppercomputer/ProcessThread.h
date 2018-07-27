#pragma once
#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#define COMPENSATION 0.1
#define LAMBDA 0.1

#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 
#include <QThread>
#include <QtCore>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <vector>

using namespace std;
using namespace cv;


class ProcessThread : public QThread
{
	Q_OBJECT
public:
	ProcessThread(QObject * parent = 0);
	~ProcessThread();

signals:
	void sendPose(Mat pose);


protected:
	void run();

private:
	bool restart;
	bool abort;
	bool updatePose;
	bool updateJacob;
	QReadWriteLock poselock;
	QWaitCondition condition;
	Mat prefeature;
	Mat feature;
	Mat pose;
	Mat prepose;
	Mat jacobian;
	Mat prejacobian;
	Mat rls;
	Mat prerls;
	Mat target;

public slots:
	void initThread(Mat initjacob, Mat initpose, Mat initfeature, Mat giventarget);
	void receivePose(Mat newpose);
	void receiveFeature(Mat newfeature);
};


#endif