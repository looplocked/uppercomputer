#include "VisualServo.h"

VisualServo::VisualServo()
{
	count = 0;
	camera = new Camera();
	robot = new RobotControl();

	prePose = Mat(6, 1, CV_64FC1);
	preFeature = Mat(8, 1, CV_64FC1);
	preJacob = Mat(8, 6, CV_64FC1);
	jacob = Mat(8, 6, CV_64FC1);
	DF = Mat(8, 6, CV_64FC1);
	theta = Mat(6, 6, CV_64FC1);
	target = Mat(8, 1, CV_64FC1);
	prerls = rls = Mat::eye(6, 6, CV_64FC1);


	target.at<double>(0) = 120;
	target.at<double>(1) = 40;
	target.at<double>(2) = 520;
	target.at<double>(3) = 40;
	target.at<double>(4) = 120;
	target.at<double>(5) = 40;
	target.at<double>(6) = 520;
	target.at<double>(7) = 440;

	camera->initial();
	Sleep(3000);
	robot->initial();
	Sleep(3000);
}

VisualServo::~VisualServo()
{
	delete camera;
	delete robot;
}

void VisualServo::initial()
{
	vector<double> temp = robot->getJointAngle();
	prePose = Mat(temp);
	vector<double> points0 = camera->getFeaturePoints();
	preFeature = Mat(points0);

	printLog("start jacobian initialization");
	thread robotInitialThread(&VisualServo::RobotInitial, this);
	thread robotVisualServoThread(&VisualServo::servo, this);
	robotInitialThread.detach();
	robotVisualServoThread.detach();
}

void VisualServo::RobotInitial()
{
	while (true) {
		if (count < 6) {
			Mat targetPose = prePose.clone();
			targetPose.at<double>(count) += 0.02;
			printLog("target pose is " + matToStr(targetPose.t()));
			vector<double> bepose = robot->getJointAngle();
			while (norm(Mat(bepose) - prePose) > 0.05) bepose = robot->getJointAngle();
			printLog("before movement, pose is " + matToStr(prePose.t()));
			printLog("before movement, feature is " + matToStr(preFeature.t()));
			robot->movej(vector<double>{ targetPose.at<double>(0),
				targetPose.at<double>(1), targetPose.at<double>(2),
				targetPose.at<double>(3), targetPose.at<double>(4),
				targetPose.at<double>(5) }, 0.1, 0.1);

			Sleep(3000);

			Mat curPose;
			vector<double> temp = robot->getJointAngle();
			curPose = Mat(temp);
			printLog("after movement pose is " + matToStr(curPose.t()));
			vector<double> curPoints = camera->getFeaturePoints();

			while (curPoints.size() != 8) curPoints = camera->getFeaturePoints();
			Mat curFeature = Mat(curPoints);
			printLog("after movement feature is " + matToStr(curFeature.t()));
			theta.col(count) = curPose - prePose;
			printLog("delta pose is " + matToStr((curPose - prePose).t()));
			DF.col(count) = curFeature - preFeature;
			printLog("delta feature is " + matToStr((curFeature - preFeature).t()));

			pose = prePose = curPose;
			feature = preFeature = curFeature;

			lock_guard<mutex> lk(count_mtx);
			count++;
		}
		else {
			preJacob = jacob = DF * theta.inv();
			printLog("DF matrix is " + matToStr(DF));
			printLog("theta matrix is " + matToStr(theta));
			printLog("jacobian is " + matToStr(jacob));
			init_ready.notify_one();
			return;
		}
	}
}

void VisualServo::servo()
{
	while (true) {
		unique_lock<mutex> lk(count_mtx);
		init_ready.wait(lk, [&] { return count == 6; });

		Mat e = feature - target;
		Mat v = -preJacob.inv() * e;

		pose = prePose + LAMBDA * v;

		robot->movej(vector<double>{pose.at<double>(0), pose.at<double>(1), \
			pose.at<double>(2), pose.at<double>(3), pose.at<double>(4), pose.at<double>(5)}, 0.1, 0.1);
		while (robot->isReachedJ(vector<double>{pose.at<double>(0), pose.at<double>(1), \
			pose.at<double>(2), pose.at<double>(3), pose.at<double>(4), pose.at<double>(5)}, 0.002))
		{
			Sleep(2000);
		}

		feature = Mat(camera->getFeaturePoints());
		Mat deltafeature = feature - preFeature;
		Mat deltapose = pose - prePose;
		jacob = preJacob + (deltafeature - preJacob * deltapose.t()) * deltapose * prerls \
			/ (COMPENSATION * deltapose * prerls * deltapose.t());
		rls = 1 / COMPENSATION * (prerls - prerls * (deltapose.t() * deltapose) * prerls)\
			/ (COMPENSATION + deltapose * prerls * deltapose.t());

		prePose = pose;
		preFeature = feature;
		prerls = rls;
		preJacob = jacob;

		if (camera->isReachedI(target, 10))
			return;
	}
}

string VisualServo::matToStr(Mat m) {
	string res = "";
	for (int i = 0; i < m.rows; i++) {
		res += "[";
		for (int j = 0; j < m.cols; j++) {
			res += to_string(m.at<double>(i, j)) + ", ";
		}
		res += "]\n";
	}
	return res;
}

void VisualServo::printLog(string log) {
	ofstream fout;
	SYSTEMTIME sys;
	::GetLocalTime(&sys);

	fout.open("log.txt", ios_base::in | ios_base::app);
	fout << "[" << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "." << sys.wMilliseconds << "]\t" << log << endl;
	fout.close();
}