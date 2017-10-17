#include "camerathread.h"


CameraThread::CameraThread(QObject * parent) : 
	QThread(parent)
{
	stopped = false;
}

void CameraThread::run()
{
	g_imagelock.lockForWrite();

	Mat temp;
	//QImage originimage, featureimage;

	g_originimg = g_cam.getImage(g_oniColorStreamparam);
	cv::cvtColor(g_originimg, temp, COLOR_RGB2GRAY);
	threshold(temp, temp, 130, 255, 3);
	medianBlur(temp, g_featureimg, 7);

	g_imagelock.unlock();

	stopped = false;
}

void CameraThread::stop()
{
	stopped = true;
}