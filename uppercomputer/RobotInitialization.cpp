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
		robot->PoseSendInitialize("robot");
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

	target.at<double>(0) = 120;
	target.at<double>(1) = 40;
	target.at<double>(2) = 520;
	target.at<double>(3) = 40;
	target.at<double>(4) = 120;
	target.at<double>(5) = 40;
	target.at<double>(6) = 520;
	target.at<double>(7) = 440;

	timer->start(100);
	printLog("initial timer start");
}

void RobotInitialization::moveAndRecord() {
	if (count < 7) {
		printLog("startMove!");
		Mat targetPose(prePose);
		targetPose.at<double>(count) += 0.01;
		robot->jointMove(vector<double>{ targetPose.at<double>(0),
			targetPose.at<double>(1), targetPose.at<double>(2),
			targetPose.at<double>(3), targetPose.at<double>(4),
			targetPose.at<double>(5) });
		printLog("targetPose is " + MatToStr(targetPose.t()));

		Mat curPose;
		vector<double> temp = robot->readPose();
		printLog("current pose is " + MatToStr(Mat(temp).t()));
		// for (int i = 0; i < 6; i++) curPose.at<double>(i) = temp[i];
		curPose = Mat(temp);
		while (norm(curPose - targetPose) > 0.01 * 0.01) { //如果还未移动到位，则等待一会后再读取关节角
			printLog("the robot is not ready");
			// printLog("the pose error is " + MatToStr(curPose - targetPose));
			_sleep(30);
			temp = robot->readPose();
			//for (int i = 0; i < 6; i++) curPose.at<double>(i) = temp[i];
			curPose = Mat(temp);
			printLog("current pose is " + MatToStr(Mat(temp).t()));
		}
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
		printLog(MatToStr(jacobian));
		timer->stop();
		emit initReady(jacobian, prePose, preFeature, target);
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