#pragma once
#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include "cameradisplay.h"
#include "uppercomputer.h"

extern Mat g_originimg, g_featureimg;
extern CameraDisplay g_cam;
//extern Device g_deviceparam;
extern VideoStream g_oniColorStreamparam;
extern QReadWriteLock g_imagelock;

class CameraThread : public QThread
{
	Q_OBJECT
public:
	explicit CameraThread(QObject * parent = 0);
	void stop();

protected:
	void run();

private:
	volatile bool stopped;
};


#endif // !CAMERA_H
