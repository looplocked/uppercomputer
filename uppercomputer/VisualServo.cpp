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
	rls = Mat::eye(6, 6, CV_64FC1);
	prerls = Mat::eye(6, 6, CV_64FC1);

#if cube
		target.at<double>(0) = 189;
		target.at<double>(1) = 108;
		target.at<double>(2) = 427;
		target.at<double>(3) = 106;
		target.at<double>(4) = 434;
		target.at<double>(5) = 348;
		target.at<double>(6) = 194;
		target.at<double>(7) = 351;

#else
		target.at<double>(0) = 201;
		target.at<double>(1) = 36;
		target.at<double>(2) = 453;
		target.at<double>(3) = 36;
		target.at<double>(4) = 453;
		target.at<double>(5) = 441;
		target.at<double>(6) = 201;
		target.at<double>(7) = 441;
#endif

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
	prePose = Mat(temp).clone();
	vector<double> points0 = camera->getFeaturePoints();
	preFeature = Mat(points0).clone();

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

			vector<double> temp = robot->getJointAngle();
			pose = Mat(temp).clone();
			printLog("after movement pose is " + matToStr(pose.t()));
			vector<double> curPoints = camera->getFeaturePoints();

			while (curPoints.size() != 8) curPoints = camera->getFeaturePoints();
			feature = Mat(curPoints).clone();
			printLog("after movement feature is " + matToStr(feature.t()));
			theta.col(count) = pose - prePose;
			printLog("initial delta pose is " + matToStr((pose - prePose).t()));
			DF.col(count) = feature - preFeature;
			printLog("initial delta feature is " + matToStr((feature - preFeature).t()));

			prePose = pose.clone();
			preFeature = feature.clone();

			lock_guard<mutex> lk(count_mtx);
			count++;
		}
		else {
			jacob = Mat(DF * theta.inv()).clone();
			preJacob = jacob.clone();
			printLog("after initial, prePose is " + matToStr(prePose.t()));
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
	unique_lock<mutex> lk(count_mtx);
	init_ready.wait(lk, [&] { return count == 6; });
	printLog("robot initialization ready, start visual servo!");

	//thread deadServoThread(&RobotControl::deadServo, robot, 0.008, 0.1, 300);
	//deadServoThread.detach();

	while (true) {
		Mat e = feature - target;
		Mat inv_jacob;
		invert(preJacob, inv_jacob, DECOMP_SVD);
		Mat v = -inv_jacob * e;
		//printLog("the move delta is " + matToStr( LAMBDA * v.t()));

		pose = prePose + LAMBDA * v;
		printLog("before move pose is " + matToStr(Mat(prePose.t())));
		printLog("before move feature is " + matToStr(Mat(preFeature.t())));
		printLog("target pose is " + matToStr(Mat(pose.t())));

		robot->movej(vector<double>{pose.at<double>(0), pose.at<double>(1), \
			pose.at<double>(2), pose.at<double>(3), pose.at<double>(4), pose.at<double>(5)}, 0.1, 0.1);
		Sleep(3000);

		while (!robot->isReachedJ(vector<double>{pose.at<double>(0), pose.at<double>(1), \
			pose.at<double>(2), pose.at<double>(3), pose.at<double>(4), pose.at<double>(5)}, 0.002))
		{
			Mat curPose = Mat(robot->getJointAngle()).clone();
			//printLog("now the pose error is " + matToStr(Mat(curPose - pose).t()));
			Sleep(3000);
		}

		Mat curPose = Mat(robot->getJointAngle()).clone();
		printLog("after move, pose is " + matToStr(curPose.t()));
		feature = Mat(camera->getFeaturePoints()).clone();
		printLog("after move, feature is " + matToStr(feature.t()));
		Mat deltafeature = feature - preFeature;
		//printLog("after move delta feature is " + matToStr(deltafeature.t()));
		Mat deltapose = pose - prePose;
		jacob = preJacob + (deltafeature - preJacob * deltapose) * deltapose.t() * prerls \
			/ (COMPENSATION + deltapose.t() * prerls * deltapose);
		rls = 1 / COMPENSATION * (prerls - prerls * (deltapose * deltapose.t()) * prerls)\
			/ (COMPENSATION + deltapose.t() * prerls * deltapose);

		prePose = pose.clone();
		preFeature = feature.clone();
		prerls = rls.clone();
		preJacob = jacob.clone();

		if (camera->isReachedI(target, 40))
			return;
	}
}

string VisualServo::matToStr(Mat m) {
	string res = "";
	for (int i = 0; i < m.rows; i++) {
		if (i != 0) res += "			";
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