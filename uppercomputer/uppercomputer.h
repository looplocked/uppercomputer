#pragma once
#ifndef UPPERCOMPUTER_H
#define UPPERCOMPUTER_H

#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QtCore/QReadWriteLock>
#include <vector>
#include <QByteArray>
#include <QMessageBox>

#include "OpenNI.h"  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/flann.hpp"

#include "ui_uppercomputer.h"
#include "cameradisplay.h"
#include "helper.h"
#include "error.h"
#include "RobotControl.h"
#include "ProcessThread.h"
#include "RobotInitialization.h"
 

using namespace std;
using namespace cv;
using namespace openni;


class uppercomputer : public QMainWindow
{
	Q_OBJECT

public:
	uppercomputer(QWidget *parent = Q_NULLPTR);
	~uppercomputer();

private:
	Ui::uppercomputerClass ui;

	CameraDisplay *camera;
	RobotControl *robot;
	RobotInitialization *init;
	ProcessThread *processThread;

	QTimer *timer;
	cvflann::StartStopTimer *fpstimer;

signals:
	void sendPose(Mat pose);
	void sendFeature(Mat feature);
	
public slots:
	void startTimer();
	void displayCamera();
	void displayPose();
	void receivePose(Mat pose);
};



#endif