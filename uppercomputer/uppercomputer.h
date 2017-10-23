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
#include <QMetaType>
#include <vector>
#include <QByteArray>

#include "OpenNI.h"  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 

#include "ui_uppercomputer.h"
#include "cameradisplay.h"
//#include "camerathread.h"
//#include "featurethread.h"
 

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

	Device *device;
	VideoStream *onistream;
	CameraDisplay *camera;

	QTimer *cameratimer;
	QTimer *posetimer;
	QTimer *movetimer;

	QTcpSocket *socket;
	QTcpSocket *movesocket;
	
	vector<double> posevector;
	vector<double> feature;

	bool forward;
	
public slots:
    void startCameraTimer();
	void displayCamera();

	void startPoseTimer();
	void readyToRead();
	void socketReadData();

	void startMoveTimer();
	void jointMove();
};



#endif