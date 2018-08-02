#include "RobotInitialization.h"

RobotInitialization::RobotInitialization(QObject * parent) : QObject(parent)
{
	robot = new RobotControl();
	camera = new Camera();
	count = 0;

	prePose = Mat(6, 1, CV_64FC1);
	preFeature = Mat(8, 1, CV_64FC1);
	jacobian = Mat(8, 6, CV_64FC1);
	DF = Mat(8, 6, CV_64FC1);
	theta = Mat(6, 6, CV_64FC1);
	target = Mat(8, 1, CV_64FC1);

	camera->initial();
	Sleep(3000);
	robot->initial();
	Sleep(3000);

	connect(this, SIGNAL(getFeature()), this, SLOT(extractFeature()));
	connect(this, SIGNAL(moveNextStep()), this, SLOT(moveAndRecord()));
}

void RobotInitialization::startInitialize()
{
	vector<double> temp = robot->getJointAngle();
	prePose = Mat(temp);
	vector<double> points0 = camera->getFeaturePoints();
	preFeature = Mat(points0);

	target.at<double>(0) = 120;
	target.at<double>(1) = 40;
	target.at<double>(2) = 520;
	target.at<double>(3) = 40;
	target.at<double>(4) = 120;
	target.at<double>(5) = 40;
	target.at<double>(6) = 520;
	target.at<double>(7) = 440;

	printLog("start jacobian initialization");

	emit moveNextStep();
}

void RobotInitialization::moveAndRecord() {
	if (count < 6) {
		Mat targetPose = prePose.clone();
		targetPose.at<double>(count) += 0.02;
		printLog("target pose is " + MatToStr(targetPose.t()));
		vector<double> bepose = robot->getJointAngle();
		while (norm(Mat(bepose) - prePose) > 0.05) bepose = robot->getJointAngle();
		printLog("before movement, pose is " + MatToStr(prePose.t()));
		printLog("before movement, feature is " + MatToStr(preFeature.t()));
		robot->movej(vector<double>{ targetPose.at<double>(0),
			targetPose.at<double>(1), targetPose.at<double>(2),
			targetPose.at<double>(3), targetPose.at<double>(4),
			targetPose.at<double>(5) }, 0.1, 0.1);

		Sleep(3000);

		emit getFeature();
	}
	else {
		jacobian = DF * theta.inv();
		printLog("DF matrix is " + MatToStr(DF));
		printLog("theta matrix is " + MatToStr(theta));
		printLog("jacobian is " + MatToStr(jacobian));
		emit initReady(jacobian, prePose, preFeature, target);
	}
}

void RobotInitialization::extractFeature()
{
	Mat curPose;
	vector<double> temp = robot->getJointAngle();
	curPose = Mat(temp);
	printLog("after movement pose is " + MatToStr(curPose.t()));
	vector<double> curPoints = camera->getFeaturePoints();
	
	while(curPoints.size() != 8) curPoints = camera->getFeaturePoints();
	Mat curFeature = Mat(curPoints);
	printLog("after movement feature is " + MatToStr(curFeature.t()));
	theta.col(count) = curPose - prePose;
	printLog("delta pose is " + MatToStr((curPose - prePose).t()));
	DF.col(count) = curFeature - preFeature;
	printLog("delta feature is " + MatToStr((curFeature - preFeature).t()));
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