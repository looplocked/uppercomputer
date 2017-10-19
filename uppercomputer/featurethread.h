#pragma once
#ifndef FEATURETHREAD_H
#define FEATURETHREAD_H

#include <QThread>
#include <QtCore>
#include <QReadWriteLock>
#include <QWaitCondition>

#include "cameradisplay.h"



class FeatureThread : public QThread
{
	Q_OBJECT
public:
	FeatureThread(QObject * parent = 0);
	~FeatureThread();

	void transParams();

signals:
	void gotAFeature(double featureX, double featureY, double featurearea, double featureang);

protected:
	void run();

private:
	bool restart;
	bool abort;
	QReadWriteLock featurelock;
	QWaitCondition condition;
	CameraDisplay cam;
	Device device;
	VideoStream stream;

private slots:
	void getFeature();
};

#endif // !FEATURETHREAD_H
