#include "RobotControl.h"

RobotControl::RobotControl(QObject * parent) : QObject(parent) {
	posesocket = new QTcpSocket(this);
	server = new QTcpServer(this);
	movesocket = new QTcpSocket(this);
	pose = { 0,0,0,0,0,0 };
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

void RobotControl::PoseSendInitialize()
{
	int port = 8000;
	if (!server->listen(QHostAddress::Any, port)) {
		printLog("listen failed!");
		//return;
	}
	connect(server, SIGNAL(newConnection()), this, SLOT(serverNewConnect()));
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
	copy(pose.begin(), pose.end(), ostream_iterator<int>(posestream, ", "));
	string posestr = "(" + posestream.str() + ")\n";
	QString data = QString::fromStdString(posestr);
	movesocket->write(data.toLatin1());
	printLog("move successfully!");
}
