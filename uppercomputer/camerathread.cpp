#include "camerathread.h"


CameraThread::CameraThread(QObject * parent) : 
	QThread(parent)
{
	restart = false;
	abort = false;
	cam.initialize(device, stream);
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

	Mat srcimg, temp, featureimg;
	Mat originimg, map_x, map_y;
	//QImage originimage, featureimage;

	if (restart)
		break;
	if (abort)
		break;

	srcimg = cam.getImage(stream);
	originimg.create(srcimg.size(), srcimg.type());
	map_x.create(srcimg.size(), CV_32FC1);
	map_y.create(srcimg.size(), CV_32FC1);

	for (int j = 0; j < srcimg.rows; j++)
	{
		for (int i = 0; i < srcimg.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(srcimg.cols-i);
			map_y.at<float>(j, i) = static_cast<float>(j);
		}
	}
	remap(srcimg, originimg, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));


	cv::cvtColor(originimg, temp, COLOR_RGB2GRAY);
	threshold(temp, temp, 130, 255, 3);
	medianBlur(temp, featureimg, 7);
	//imshow("src", featureimg);
	//waitKey(20);
	
	if (!restart)
		emit gotAImage(originimg, featureimg);
	
	imagelock.lockForWrite();
	if (!restart)
		condition.wait(&imagelock);
	restart = false;
	imagelock.unlock();

	
	}
}

void CameraThread::transParams()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void CameraThread::getImage()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}
