#pragma once
#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#include <QtCore>
#include <QDebug>
#include <QTimer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QHostAddress>
#include <QAbstractSocket>
#include <vector>
#include <QByteArray>
#include <QObject>

#include <sstream>

using namespace std;


class RobotControl : public QObject {
	Q_OBJECT
public:
	RobotControl(QObject * parent=0);
	~RobotControl();
	
	void poseReadInitialize();
	void PoseSendInitialize();
	vector<double> readPose();
	void jointMove(vector<double> pose);

signals:
	void poseReady();

private slots:
	void readyToRead();
	void socketReadData();
	void serverNewConnect();

private:
	QTcpSocket *posesocket;
	QTcpServer *server;
	QTcpSocket *movesocket;
	vector<double> pose;
};

#endif