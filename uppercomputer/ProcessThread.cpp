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
		if (restart)
			break;
		if (abort)
			break;
		
		if (updatePose) {
			Mat e = feature - target;
			Mat v = -prejacobian.inv() * e;

			pose = prepose + LAMBDA * v.t();

			if (!restart)
				emit sendPose(pose);
			
			updatePose = false;
		}

		if (updateJacob) {
			Mat deltafeature = feature - prefeature;
			Mat deltapose = pose - prepose;
			jacobian = prejacobian + (deltafeature - prejacobian * deltapose.t()) * deltapose * prerls \
				/ (COMPENSATION * deltapose * prerls * deltapose.t());
			rls = 1 / COMPENSATION * (prerls - prerls * (deltapose.t() * deltapose) * prerls)\
				/ (COMPENSATION + deltapose * prerls * deltapose.t());

			prepose = pose;
			prefeature = feature;
			prerls = rls;
			prejacobian = jacobian;

			updateJacob = false;
		}
	}
}

void ProcessThread::initThread(Mat initjacob, Mat initpose, Mat initfeature, Mat giventarget)
{
	if (!isRunning()) {
		prejacobian = jacobian = initjacob;
		prepose = pose = initpose;
		prefeature = feature = initfeature;
		start(LowPriority);
		target = giventarget;

		prerls = rls = Mat::eye(6, 6, CV_64FC1);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void ProcessThread::receivePose(Mat newpose)
{
	if (!isRunning()) {
		pose = newpose;
		updatePose = true;
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void ProcessThread::receiveFeature(Mat newfeature)
{
	if (!isRunning()) {
		updateJacob = true;
		feature = newfeature;
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}