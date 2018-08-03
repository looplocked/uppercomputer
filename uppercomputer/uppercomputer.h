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
#include "Camera.h"
#include "helper.h"
#include "error.h"
#include "RobotControl.h"
#include "VisualServo.h"
 

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

	Camera *camera;
	RobotControl *robot;
	VisualServo *servo;

	QTimer *timer;
	cvflann::StartStopTimer *fpstimer;

	void deleteLog();

signals:
	void sendPose(Mat pose);
	void sendFeature(Mat feature);
	
public slots:
	void startTimer();
	void displayCamera();
	void displayPose();
	void startServo();
};



#endif