#pragma once
#ifndef FEATURETHREAD_H
#define FEATURETHREAD_H

#include <QThread>
#include "uppercomputer.h"


//extern double g_featurex, g_featurey, g_featurearea, g_featureang;
//extern Mat g_featureimg;
//extern QReadWriteLock g_imagelock;
//extern QReadWriteLock g_featurelock;


class FeatureThread : public QThread
{
	Q_OBJECT

public:
	explicit FeatureThread(QObject * parent = 0);
	void stop();

protected:
	void run();

private:
	volatile bool stopped;
};

#endif // !FEATURETHREAD_H
