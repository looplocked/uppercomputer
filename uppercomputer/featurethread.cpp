#include "featurethread.h"

FeatureThread::FeatureThread(QObject * parent) :
	QThread(parent)
{
	stopped = false;
}

void FeatureThread::run()
{
	
	// Ñ°ÕÒÂÖÀª
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	g_imagelock.lockForRead();
	findContours(g_featureimg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	g_imagelock.unlock();


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

	g_featurelock.lockForWrite();
	g_featurex = mc.x;
	g_featurey = mc.y;
	g_featurearea = contourArea(contour);
	RotatedRect rect = minAreaRect(contour);
	g_featureang = -rect.angle;
	g_featurelock.unlock();

	stopped = false;
}


void FeatureThread::stop()
{
	stopped = true;
}