#include "RobotInitialization.h"

RobotInitialization::RobotInitialization(QObject * parent) : QObject(parent)
{
	robot = new RobotControl();
	camera = new CameraDisplay();
	timer = new QTimer();

	try {
		camera->initialize();
	}
	catch (CameraException& camexc)
	{
		// QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
	}

	try {
		robot->poseReadInitialize();
	}
	catch (RobotException& robotexc)
	{
		// QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}

	try {
		robot->PoseSendInitialize();
	}
	catch (RobotException& robotexc)
	{
		// QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}

	connect(timer, SIGNAL(timeout()), this, SLOT(moveAndRecord()));
}

void RobotInitialization::startInitialize()
{
	vector<double> temp = robot->readPose();
	for (int i = 0; i < 6; i++) prePose.at<double>(i) = temp[i];
	vector<Point> points0;
	camera->getImageAndFeature(points0);
	Matx<double, 8, 1> preFeature = flatPoints(points0);
	timer->start(50);
}

void RobotInitialization::moveAndRecord() {
	if (count < 7) {
		Mat targetPose(prePose);
		targetPose.at<double>(count) += 0.01;
		robot->jointMove(vector<double>{ targetPose.at<double>(0),
			targetPose.at<double>(1), targetPose.at<double>(2),
			targetPose.at<double>(3), targetPose.at<double>(4),
			targetPose.at<double>(5) });

		Mat curPose;
		vector<double> temp = robot->readPose();
		for (int i = 0; i < 6; i++) curPose.at<double>(i) = temp[i];
		vector<Point> curPoints;
		camera->getImageAndFeature(curPoints);
		Mat curFeature = flatPoints(curPoints);
		theta.col(count) = curPose - prePose;
		DF.col(count) = curFeature - preFeature;
		count++;

		prePose = curPose;
		preFeature = curFeature;
	}
	else {
		jacobian = DF * theta.inv();
		timer->stop();
		emit initReady(jacobian, prePose, preFeature);
	}
}

Mat RobotInitialization::getJacobian() {
	return jacobian;
}

RobotInitialization::~RobotInitialization()
{
	delete robot;
	delete camera;
	delete timer;
}