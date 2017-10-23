#include "robotposethread.h"

RobotPoseThread::RobotPoseThread(QObject * parent) :
	QThread(parent)
{
	restart = false;
	abort = false;
	socket = new QTcpSocket();
	connect(socket, &QTcpSocket::readyRead, this, &RobotPoseThread::socketReadData);
	//connect(socket, &QTcpSocket::disconnected, this, &RobotPoseThread::socketDisconnected);
}

RobotPoseThread::~RobotPoseThread()
{
	delete this->socket;
}

void RobotPoseThread::connectRobot()
{
	QString IP = "88.88.88.89";
	int port = 30002;
	socket->abort();
	socket->connectToHost(IP, port);
}

void RobotPoseThread::run()
{
	forever{
		if (restart)
			break;
		if (abort)
			break;



		QByteArray buffer;
		int jointposeaddress = 252;
		vector<double> posevector;
		buffer = socket->readAll();
		char *buff = buffer.data();

		if (!buffer.isEmpty())
		{
			for (int i = 0; i<6; i++)
			{
				char temp[8];
				double temppose;
				for (int j = 0; j<8; j++)
				{
					temp[j] = buff[jointposeaddress + 8 * i + j];
				}
				memcpy(&temppose, temp, sizeof(temppose));
				posevector.push_back(temppose);
			}
		}

		if (!restart)
			emit gotAPose(posevector);

		poselock.lockForWrite();
		if (!restart)
			condition.wait(&poselock);
		restart = false;
		poselock.unlock();
	}
}

void RobotPoseThread::transParams()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}

void RobotPoseThread::getPose()
{
	if (!isRunning()) {
		start(LowPriority);
	}
	else {
		restart = true;
		condition.wakeOne();
	}
}