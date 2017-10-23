#include "featurethread.h"

FeatureThread::FeatureThread(QObject * parent) :
	QThread(parent)
{
	restart = false;
	abort = false;
	cam.initialize(device, stream);
}

FeatureThread::~FeatureThread()
{
	featurelock.lockForWrite();
	abort = true;
	featurelock.unlock();

	wait();
}

void FeatureThread::run()
{
	forever{
		Mat featureimg = cam.getImage(stream);
		cv::cvtColor(featureimg, featureimg, COLOR_RGB2GRAY);
		threshold(featureimg, featureimg, 130, 255, 3);
		medianBlur(featureimg, featureimg, 7);

		//imshow("src1", featureimg);
		//waitKey(20);

		if (restart)
			break;
		if (abort)
			break;

		// Ñ°ÕÒÂÖÀª
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(featureimg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

		double featurex = 0, featurey = 0, featurearea = 0, featureang = 0;


		vector<Point> contour = contours[0];
		if (contours.size() > 1)
		{
			for (auto iter = contours.begin(); iter != contours.end(); iter++)
			{
				if ((*iter).size() > contour.size())
					contour = *iter;
			}
		}

		//¼ÆËãÌØÕ÷Öµ
		Moments mu = moments(contour, false);
		Point2f mc;
		mc = Point2f(static_cast<float>(mu.m10 / mu.m00), static_cast<float>(mu.m01 / mu.m00));

		featurex = mc.x;
		featurey = mc.y;
		featurearea = contourArea(contour);
		RotatedRect rect = minAreaRect(contour);
		featureang = -rect.angle;

		if (!restart)
			emit gotAFeature(featurex, featurey, featurearea, featureang);

		featurelock.lockForWrite();
		if (!restart)
			condition.wait(&featurelock);
		restart = false;
		featurelock.unlock();
    }
}


void FeatureThread::transParams()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void FeatureThread::getFeature()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}