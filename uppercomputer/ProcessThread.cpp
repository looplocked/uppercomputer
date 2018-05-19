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
			emit sendPose(vector<float>{pose.at<float>(0), pose.at<float>(1), pose.at<float>(1), \
				pose.at<float>(3), pose.at<float>(4), pose.at<float>(5) });
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

void ProcessThread::receiveData(vector<float> newpose, vector<float> newfeature)
{
	pose = Mat(newpose);
	feature = Mat(newfeature);
}