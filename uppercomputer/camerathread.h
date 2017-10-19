#pragma once
#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QtCore>
#include <QReadWriteLock>
#include <QWaitCondition>


#include "cameradisplay.h"


//extern Mat g_originimg, g_featureimg;
//extern CameraDisplay g_cam;
//extern Device g_deviceparam;
//extern VideoStream g_oniColorStreamparam;
//extern QReadWriteLock g_imagelock;

class CameraThread : public QThread
{
	Q_OBJECT
public:
	CameraThread(QObject * parent = 0);
	~CameraThread();

	void transParams(CameraDisplay &camparam, VideoStream &streamparam);

signals:
	void gotAImage(Mat originimg, Mat featureimg);

protected:
	void run();

private:
	bool restart;
	bool abort;
	QReadWriteLock imagelock;
	QWaitCondition condition;
	CameraDisplay cam;
	Device device;
	VideoStream stream;

private slots:
	void getImage();
};


#endif // !CAMERA_H
