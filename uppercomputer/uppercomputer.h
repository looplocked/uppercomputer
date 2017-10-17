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

extern Mat g_originimg, g_featureimg;
extern Device g_deviceparam;
extern VideoStream g_oniColorStreamparam;
extern double g_posex, g_posey, g_posez, g_poserx, g_posery, g_poserz;
extern double g_featurex, g_featurey, g_featurearea, g_featureang;
extern CameraDisplay g_cam;
extern QReadWriteLock g_imagelock;
extern QReadWriteLock g_poselock;
extern QReadWriteLock g_featurelock;

class FeatureThread;
class CameraThread;

class uppercomputer : public QMainWindow
{
	Q_OBJECT

public:
	uppercomputer(QWidget *parent = Q_NULLPTR);

private:
	Ui::uppercomputerClass ui;
	QTimer *timer;
	QTcpServer *server;
	QTcpSocket *socket;
	FeatureThread *feature;
	CameraThread *camera;
	


public slots:
    void showImage();
	void startTimer();
	void closeCam();
	void disFeature();
	void disPose();
	void serverNewConnect();
	void socketReadData();
	void socketDisconnected();
};



#endif