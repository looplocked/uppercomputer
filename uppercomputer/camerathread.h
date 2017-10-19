#pragma once
#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QtCore>
#include <QReadWriteLock>
#include <QWaitCondition>


#include "cameradisplay.h"


class CameraThread : public QThread
{
	Q_OBJECT
public:
	CameraThread(QObject * parent = 0);
	~CameraThread();

	void transParams();

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
