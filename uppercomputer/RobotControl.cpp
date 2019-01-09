#pragma comment(lib, "Ws2_32.lib")
#include "RobotControl.h"

RobotControl::RobotControl(void)
{
	globalPose.resize(6);
}

RobotControl::~RobotControl(void)
{
	close();
}


void  RobotControl::initial()
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return;
	if ((LOBYTE(wsaData.wVersion) != 1) || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup(); return;
	}

	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("211.80.60.51");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(30003);
	bind(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	int fail = connect(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//开始连接
	if (fail) {
		printLog("failed to connect to server!");
		_getch();
		return;
	}

	thread pt(&RobotControl::poseReadThread, this);
	pt.detach();
	printLog("pose read thread detach succeeded!");

	
}

vector<double> RobotControl::getJointAngle()
{
	while (true) {
		if (mtx.try_lock()) {
			vector<double> pose = globalPose;
			mtx.unlock();
			return pose;
		}
	}
}

void  RobotControl::movej(vector<double>& pose, double speed, double a)
{
	int len = sizeof(SOCKADDR);
	const char* sendBuf;
	string command = "movej([" + doubleToString((double)pose[0]) + ", " \
		+ doubleToString((double)pose[1]) + ", " + doubleToString(pose[2]) \
		+ ", " + doubleToString(pose[3]) + ", " + doubleToString(pose[4]) \
		+ ", " + doubleToString(pose[5]) + "], a=" + doubleToString(a) \
		+ ", v=" + doubleToString(speed) +  ")\n";
	//string command = "movej([" + doubleToString((double)pose[0]) + "," + doubleToString((double)pose[1]) + "," + doubleToString(pose[2]) + "," + doubleToString(pose[3]) + "," + doubleToString(pose[4]) + "," + doubleToString(pose[5]) + "]" + ")\n";
	sendBuf = command.c_str();
	int state = sendto(socketClient, sendBuf, strlen(sendBuf), 0, (SOCKADDR *)&addrSrv, len);
	//int state = send(socketClient, sendBuf, strlen(sendBuf) + 1, 0);
}

void RobotControl::servoj(vector<double>& pose)
{
	/*try {
		safetyCheck(pose);
	}
	catch (RobotException &e) {
		printLog("Robot out of control " + string(e.what()) + "!");
	}*/
	vector<double> deltaPose{ pose[0] - poseQueue.back()[0], \
		pose[1] - poseQueue.back()[1], pose[2] - poseQueue.back()[2],\
		pose[3] - poseQueue.back()[3], pose[4] - poseQueue.back()[4],\
		pose[5] - poseQueue.back()[5] };
	double max_value = 0;
	for (double p : deltaPose)
		max_value = max_value > abs(p) ? max_value : abs(p);
	int step = ceil(max_value / STEPSIZE);
	for (int i = 1; i <= step; i++) {
		while (true) {
			if (queue_mtx.try_lock()) {
				poseQueue.push_back(vector<double>{poseQueue.back()[0] \
					+ i / step * deltaPose[0], poseQueue.back()[1] \
					+ i / step * deltaPose[1], poseQueue.back()[2] \
					+ i / step * deltaPose[2], poseQueue.back()[3] \
					+ i / step * deltaPose[3], poseQueue.back()[4] \
					+ i / step * deltaPose[4], poseQueue.back()[5] \
					+ i / step * deltaPose[5]});
				queue_mtx.unlock();
				printLog("now the delta pose " + to_string(i)+ "is pushed into queue");
				break;
			}
		}
		
	}
}

void RobotControl::Stop()
{
	int len = sizeof(SOCKADDR);
	char sendBuf[55] = { '\n' };
	sendBuf[0] = 'S';
	sendBuf[1] = 't';
	sendBuf[2] = '\n';
	sendto(socketClient, sendBuf, strlen(sendBuf), 0, (SOCKADDR *)&addrSrv, len);
}

bool RobotControl::isReachedJ(vector<double>& target, double threshold)
{
	std::vector<double> pose;
	pose = getJointAngle();
	return (abs(pose[0] - target[0]) < threshold) && (abs(pose[1] - target[1]) < threshold)
		&& (abs(pose[2] - target[2]) < threshold) && (abs(pose[3] - target[3]) < threshold)
		&& (abs(pose[4] - target[4]) < threshold) && (abs(pose[5] - target[5]) < threshold) ? true : false;
}

void RobotControl::safetyCheck(vector<double>& pose)
{
	vector<Mat> transMat(6, Mat(4, 4, CV_64FC1));
	vector<double> d{ 0.1273, 0, 0, 0.163941, 0.1157, 0.0922 };
	vector<double> a{ 0, -0.612, -0.5723, 0, 0, 0 };
	vector<double> alpha{ 1.570796327, 0, 0, 1.570796327, -1.570796327, 0 };
	for (int i = 0; i < 6; i++) {
		transMat[i].at<double>(0, 0) = cos(pose[i]);
		transMat[i].at<double>(0, 1) = -sin(pose[i]);
		transMat[i].at<double>(0, 3) = a[i];
		transMat[i].at<double>(1, 0) = sin(pose[i]) * cos(alpha[i]);
		transMat[i].at<double>(1, 1) = cos(pose[i]) * cos(alpha[i]);
		transMat[i].at<double>(1, 2) = -sin(alpha[i]);
		transMat[i].at<double>(1, 3) = -sin(alpha[i]) * d[i];
		transMat[i].at<double>(2, 0) = sin(pose[i]) * sin(alpha[i]);
		transMat[i].at<double>(2, 1) = cos(pose[i]) * sin(alpha[i]);
		transMat[i].at<double>(2, 2) = cos(alpha[i]);
		transMat[i].at<double>(2, 3) = cos(alpha[i]) * d[i];
		transMat[i].at<double>(3, 3) = 1;
	}

	Mat toolCoord = transMat[0] * transMat[1] * transMat[2] * transMat[3] * transMat[4] * transMat[5];
	if (toolCoord.at<double>(0, 3) > 0.3)
	{
		throw RobotException("too left " + to_string(toolCoord.at<double>(0, 3)));
	}
	else if (toolCoord.at<double>(0, 3) < -0.3) {
		throw RobotException("too right " + to_string(toolCoord.at<double>(0, 3)));
	}
	else if (toolCoord.at<double>(1, 3) > 0.3)
	{
		throw RobotException("too front " + to_string(toolCoord.at<double>(1, 3)));
	}
	else if (toolCoord.at<double>(1, 3) < -0.3)
	{
		throw RobotException("too back " + to_string(toolCoord.at<double>(1, 3)));
	}
	else if (toolCoord.at<double>(2, 3) > 0.3)
	{
		throw RobotException("too high " + to_string(toolCoord.at<double>(2, 3)));
	}
	else if (toolCoord.at<double>(2, 3) < 0)
	{
		throw RobotException("too low " + to_string(toolCoord.at<double>(2, 3)));
	}
}

void RobotControl::deadServo(double t, double lookahead_time, double gain)
{
	vector<double> init_pose = getJointAngle();
	while (true) {
		if (queue_mtx.try_lock()) {
			poseQueue.push_back(init_pose);
			queue_mtx.unlock();
			break;
		}
	}
	while (true) {
		int len = sizeof(SOCKADDR);
		const char* sendBuf;
		vector<double> pose = poseQueue.front();
		string command = "servoj([" + doubleToString((double)pose[0]) + ", " \
			+ doubleToString((double)pose[1]) + ", " + doubleToString(pose[2]) \
			+ ", " + doubleToString(pose[3]) + ", " + doubleToString(pose[4]) \
			+ ", " + doubleToString(pose[5]) + "], t=" + doubleToString(t) \
			+ ", lookahead_time=" + doubleToString(lookahead_time) + +", gain=" \
			+ doubleToString(gain) + ")\n";
		sendBuf = command.c_str();
		int state = sendto(socketClient, sendBuf, strlen(sendBuf), 0, (SOCKADDR *)&addrSrv, len);
		printLog("servoj([" + doubleToString((double)pose[0]) + ", " \
			+ doubleToString((double)pose[1]) + ", " + doubleToString(pose[2]) \
			+ ", " + doubleToString(pose[3]) + ", " + doubleToString(pose[4]) \
			+ ", " + doubleToString(pose[5]) + "], t=" + doubleToString(t) \
			+ ", lookahead_time=" + doubleToString(lookahead_time) + +", gain=" \
			+ doubleToString(gain) + ")\n");
		if (poseQueue.size() > 1) {
			while (true) {
				if (queue_mtx.try_lock()) {
					poseQueue.pop_front();
					queue_mtx.unlock();
					break;
				}
			}
		}
		Sleep(100);
	}
}

void RobotControl::poseReadThread()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return;
	if ((LOBYTE(wsaData.wVersion) != 1) || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup(); return;
	}
	SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("211.80.60.51");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(30003);
	bind(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	int fail = connect(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//开始连接
	if (fail) {
		cout << "与服务端连接失败！程序将退出..." << endl;
		_getch();
		return;
	}

	char recvBuf[DATA_LENGTH];
	while (true) {
		int len = sizeof(SOCKADDR);
		recvfrom(socketClient, recvBuf, DATA_LENGTH, 0, (SOCKADDR *)&addrSrv, &len);
		int ActualJointVelocities_StartAddress = 252;        //joint速度地址
		BYTE temp[8];
		double TCP_vector[6]; //返回的6个参数

		for (int j = 0; j < 6; j++) //6个参数
		{
			for (int i = 0; i < 8; i++) //每个参数8个字节
			{
				temp[i] = *(recvBuf + ActualJointVelocities_StartAddress + 7 - i + 8 * j); //注意逆序

			}
			memcpy(&TCP_vector[j], temp, sizeof(TCP_vector[j]));//字节数组转double
		}
		if (mtx.try_lock()) {
			for (int i = 0; i < 6; i++)
				globalPose[i] = *(TCP_vector + i);
			mtx.unlock();
		}
	}
}


string RobotControl::doubleToString(double input)
{
	std::stringstream ss;
	ss << input;
	return ss.str();
}

string RobotControl::intToString(int input)
{
	std::stringstream ss;
	ss << input;
	return ss.str();
}
void RobotControl::close()
{
	closesocket(socketClient);
}

void RobotControl::printLog(string log) {
	ofstream fout;
	SYSTEMTIME sys;
	::GetLocalTime(&sys);

	fout.open("log.txt", std::ios_base::in | std::ios_base::app);
	fout << "[" << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "." << sys.wMilliseconds << "]\t" << log << endl;
	fout.close();
}

void RobotControl::deleteLog() {
	ofstream fout;
	fout.open("log.txt", ofstream::out | ofstream::trunc);
	fout.close();
}
