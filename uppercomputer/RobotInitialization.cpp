#include "RobotInitialization.h"

RobotInitialization::RobotInitialization(QObject * parent) : QObject(parent)
{
	robot = new RobotControl();
	camera = new CameraDisplay();

	count = 0;

	prePose = Mat(6, 1, CV_64FC1);
	preFeature = Mat(8, 1, CV_64FC1);
	jacobian = Mat(8, 6, CV_64FC1);
	DF = Mat(8, 6, CV_64FC1);
	theta = Mat(6, 6, CV_64FC1);
	target = Mat(8, 1, CV_64FC1);

	try {
		camera->initialize();
	}
	catch (CameraException& camexc)
	{
		// QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
	}

	try {
		robot->initial();
	}
	catch (RobotException& robotexc)
	{
		// QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}


	connect(this, SIGNAL(getFeature()), this, SLOT(extractFeature()));
	connect(this, SIGNAL(moveNextStep()), this, SLOT(moveAndRecord()));
}

void RobotInitialization::startInitialize()
{
	vector<double> temp = robot->getJointAngle();
	for (int i = 0; i < 6; i++) prePose.at<double>(i) = temp[i];
	vector<Point> points0;
	camera->getImageAndFeature(points0);
	Mat preFeature = flatPoints(points0);

	target.at<double>(0) = 120;
	target.at<double>(1) = 40;
	target.at<double>(2) = 520;
	target.at<double>(3) = 40;
	target.at<double>(4) = 120;
	target.at<double>(5) = 40;
	target.at<double>(6) = 520;
	target.at<double>(7) = 440;

	emit moveNextStep();

	printLog("start jacobian initialization");
}

void RobotInitialization::moveAndRecord() {
	if (count < 6) {
		printLog("startMove!");
		printLog("prePose is " + MatToStr(prePose.t()));
		Mat targetPose(prePose);
		targetPose.at<double>(count) += 0.05;
		printLog("targetPose is " + MatToStr(targetPose.t()));
		vector<double> bepose = robot->getJointAngle();
		printLog("before movement, pose is " + MatToStr(Mat(bepose).t()));
		robot->movej(vector<double>{ targetPose.at<double>(0),
			targetPose.at<double>(1), targetPose.at<double>(2),
			targetPose.at<double>(3), targetPose.at<double>(4),
			targetPose.at<double>(5) }, 0.5, 1.4);

		Sleep(300);

		emit getFeature();
	}
	else {
		jacobian = DF * theta.inv();
		printLog(MatToStr(jacobian));
		emit initReady(jacobian, prePose, preFeature, target);
	}
}

void RobotInitialization::extractFeature()
{
	Mat curPose;
	vector<double> temp = robot->getJointAngle();
	curPose = Mat(temp);
	printLog("after movement pose is " + MatToStr(curPose.t()));
	vector<Point> curPoints;
	camera->getImageAndFeature(curPoints);
	Mat curFeature = flatPoints(curPoints);
	theta.col(count) = curPose - prePose;
	DF.col(count) = curFeature - preFeature;
	count++;

	prePose = curPose;
	preFeature = curFeature;

	emit moveNextStep();
}

Mat RobotInitialization::getJacobian() {
	return jacobian;
}

RobotInitialization::~RobotInitialization()
{
	delete robot;
	delete camera;
}