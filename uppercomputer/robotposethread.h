#pragma once
#ifndef ROBOTPOSETHREAD_H
#define ROBOTPOSETHREAD_H

#include <QThread>
#include <QtCore>
#include <QReadWriteLock>
#include <QWaitCondition>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#include <vector>
#include <QByteArray>

using namespace std;

class RobotPoseThread : public QThread
{
	Q_OBJECT
public:
	RobotPoseThread(QObject * parent = 0);
	~RobotPoseThread();

	void transParams();

signals:
	void gotAPose(vector<double> pose);

protected:
	void run();

private:
	bool restart;
	bool abort;
	QReadWriteLock poselock;
	QWaitCondition condition;
	QTcpSocket *socket;

private slots:
	void getPose();
	void connectRobot();
};


#endif