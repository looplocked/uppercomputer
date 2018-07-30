#include "RobotControl.h"

RobotControl::RobotControl(QObject * parent) : QObject(parent) {
	posesocket = new QTcpSocket(this);
	server = new QTcpServer(this);
	movesocket = new QTcpSocket(this);
	pose = { 0,0,0,0,0,0 };
	printLog("robot control constructor start!");
}

RobotControl::~RobotControl () {
	delete posesocket;
	delete server;
	delete movesocket;
}

void RobotControl::poseReadInitialize()
{
	QString IP = "88.88.88.89";
	int port = 30003;
	posesocket->abort();
	posesocket->connectToHost(IP, port);
	if (!posesocket->waitForConnected(3))
	{
		qDebug() << "Connection failed!";
		return;
	}
	qDebug() << "Connect successfully!";
}

void RobotControl::PoseSendInitialize(string log)
{
	int port = 8000;
	if (!server->listen(QHostAddress::Any, port)) {
		printLog(log + " send initialization failed!");
		return;
	}
	connect(server, SIGNAL(newConnection()), this, SLOT(serverNewConnect()));
	printLog(log + " send initialization succeeded!");
}

vector<double> RobotControl::readPose()
{
	//emit poseReady();
	QByteArray buffer;
	int jointposeaddress = 252;
	buffer = posesocket->readAll();
	char *buff = buffer.data();

	if (!buffer.isEmpty())
	{
		for (int i = 0; i<6; i++)
		{
			char temp[8];
			double temppose;
			for (int j = 0; j<8; j++)
			{
				temp[j] = buff[jointposeaddress + 8 * i + 7 - j];
			}
			memcpy(&temppose, temp, sizeof(temppose));
			pose[i] = temppose;
		}
	}
	return pose;
}


void RobotControl::serverNewConnect()
{
	movesocket = server->nextPendingConnection();
	printLog("new connection succeed!");
}

void RobotControl::jointMove(vector<double> pose)
{
	stringstream posestream;
	copy(pose.begin(), pose.end(), ostream_iterator<double>(posestream, ", "));
	string posestr = posestream.str();
	posestr = posestr.substr(0, posestr.size() - 2);
	posestr = "(" + posestr + ")\n";
	QString data = QString::fromStdString(posestr);
	printLog("pose string is " + data.toStdString());
	movesocket->write(data.toLatin1());
	printLog("Pose sent successfully!");
}
