#include "camerathread.h"


CameraThread::CameraThread(QObject * parent) : 
	QThread(parent)
{
	restart = false;
	abort = false;
}

CameraThread::~CameraThread()
{
	imagelock.lockForWrite();
	abort = true;
	imagelock.unlock();

	wait();
}

void CameraThread::run()
{
	forever{

	Mat originimg, temp, featureimg;
	//QImage originimage, featureimage;

	if (restart)
		break;
	if (abort)
		return;

	originimg = cam.getImage(stream);
	cv::cvtColor(originimg, temp, COLOR_RGB2GRAY);
	threshold(temp, temp, 130, 255, 3);
	medianBlur(temp, featureimg, 7);
	
	if (restart)
		emit gotAImage(originimg, featureimg);
	
	imagelock.lockForRead();
	if (!restart)
		condition.wait(&imagelock);
	restart = false;
	imagelock.unlock();
	}
}

void CameraThread::transParams(CameraDisplay &camparam, VideoStream &streamparam)
{
	cam = camparam;
	stream = streamparam;
}