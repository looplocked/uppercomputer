#include "ProcessThread.h"

ProcessThread::ProcessThread(QObject * parent) :
	QThread(parent)
{
	restart = false;
	abort = false;
	
}

ProcessThread::~ProcessThread()
{
	poselock.lockForWrite();
	abort = true;
	poselock.unlock();
	wait();
}

void ProcessThread::run()
{
	forever{
		Mat deltafeature = feature - prefeature;
		Mat deltapose = pose - prepose;
		jacobian = prejacobian + (deltafeature - prejacobian * deltapose.t()) * deltapose * prerls \
				/ (COMPENSATION * deltapose * prerls * deltapose.t());
		rls = 1 / COMPENSATION * (prerls - prerls * (deltapose.t() * deltapose) * prerls)\
			/ (COMPENSATION + deltapose * prerls * deltapose.t());
		prepose = pose;
		Mat e = feature - target;
		Mat v = -jacobian.inv() * e;
		pose = pose + LAMBDA * v.t();

		if (!restart)
			emit sendPose(vector<double>{pose.at<double>(0), pose.at<double>(1), pose.at<double>(1), \
				pose.at<double>(3), pose.at<double>(4), pose.at<double>(5) });
	}
}

void ProcessThread::transParams()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void ProcessThread::startThread()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void ProcessThread::receiveData(vector<double> newpose, vector<Point> newfeature)
{
	pose = Mat(newpose);
	feature = Mat(newfeature);
}