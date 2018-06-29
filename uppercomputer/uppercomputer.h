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
	ProcessThread *processThread;

	QTimer *timer;
	cvflann::StartStopTimer *fpstimer;

signals:
	void sendData(vector<double> pose, vector<Point> feature);
	
public slots:
	void startTimer(int ms);
	void displayCamera();
	void displayPose();
	void receiveData(vector<double> pose);
};



#endif