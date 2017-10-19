#pragma once
#ifndef UPPERCOMPUTER_H
#define UPPERCOMPUTER_H

#include <QtWidgets/QMainWindow>
#include <QtCore>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QtCore/QReadWriteLock>
#include <QMetaType>

#include "OpenNI.h"  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 

#include "ui_uppercomputer.h"
#include "cameradisplay.h"
#include "camerathread.h"
#include "featurethread.h"
 

using namespace std;
using namespace cv;
using namespace openni;



class uppercomputer : public QMainWindow
{
	Q_OBJECT

public:
	uppercomputer(QWidget *parent = Q_NULLPTR);

private:
	Ui::uppercomputerClass ui;
	QTimer *imagetimer;
	QTimer *featuretimer;
	QTcpServer *server;
	QTcpSocket *socket;
	FeatureThread *feature;
	CameraThread *camera;
	


public slots:
    void startImageTimer();
    void showImage(Mat originimg, Mat featureimg);
	void closeCam();
	
	void startFeatureTimer();
	void disFeature(double featurex, double featurey, double featurearea, double featureang);
	void closeFeature();

	//void disPose();
	//void serverNewConnect();
	//void socketReadData();
	//void socketDisconnected();
};



#endif