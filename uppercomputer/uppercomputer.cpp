#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	cameratimer = new QTimer(this);
	posetimer = new QTimer(this);
	movetimer = new QTimer(this);

	camera = new CameraDisplay();
	device = new Device();
	onistream = new VideoStream();
	fpstimer = new cvflann::StartStopTimer;

	posevector = { 0, 0, 0, 0, 0, 0 };
	feature = { 0, 0, 0, 0 };

	socket = new QTcpSocket(this);
	server = new QTcpServer(this);
	//movesocket = new QTcpSocket(this);
	try {
		camera->initialize(*device, *onistream);
	}
	catch (CameraException& camexc)
	{
		//QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
	}

	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startCameraTimer()));
	connect(cameratimer, SIGNAL(timeout()), this, SLOT(displayCamera()));

	
	connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT(startPoseTimer()));
	connect(posetimer, SIGNAL(timeout()), this, SLOT(readyToRead()));

	connect(server, SIGNAL(newConnection()), this, SLOT(serverNewConnect()));
	connect(ui.ButtonMove, SIGNAL(clicked()), this, SLOT(startMoveTimer()));
	connect(movetimer, SIGNAL(timeout()), this, SLOT(jointMove()));
}

void uppercomputer::startCameraTimer()
{
	if (ui.ButtonOpenCam->text() == tr("OpenCam"))
	{
		cameratimer->start(50);

		ui.ButtonOpenCam->setText("CloseCam");
	}
	else
	{
		cameratimer->stop();
		ui.ButtonOpenCam->setText("OpenCam");
		ui.LabelCamera->clear();
		ui.LabelFeature->clear();
		ui.LineEditFeatureX->clear();
		ui.LineEditFeatureY->clear();
		ui.LineEditFeatureArea->clear();
		ui.LineEditFeatureAngle->clear();
	}
}

 void uppercomputer::displayCamera()
{
	double fps;

	Mat srcimg, originimg;
	QImage qoriginimg, qfeatureimg;

	fpstimer->start();
	try
	{
		srcimg = camera->getImage(*onistream);
	}
	catch (CameraException& camexc)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
		exit(-1);
	}

	originimg = mirrorMap(srcimg);


	vector<Point> Points;
	Mat drawImg2 = processAndGetFeature(srcimg, Points);

	fpstimer->stop();
	fps = 1.0 / fpstimer->value;
	fpstimer->reset();

	QString fpsstr = QString("%1").arg(fps);

	ui.FPSLineEdit->clear();
	ui.FPSLineEdit->setText(fpsstr);


	qoriginimg = QImage((const uchar*)(originimg.data), originimg.cols, originimg.rows, originimg.cols*originimg.channels(), QImage::Format_RGB888);
	qfeatureimg = QImage((const uchar*)(drawImg2.data), drawImg2.cols, drawImg2.rows, drawImg2.cols*drawImg2.channels(), QImage::Format_RGB888);

	ui.LabelCamera->clear();
	ui.LabelFeature->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(qoriginimg));
	ui.LabelFeature->setPixmap(QPixmap::fromImage(qfeatureimg));
	ui.LabelCamera->show();
	ui.LabelFeature->show();




	QString point1 = Points.size()  < 1 ? "" : QString("%1, %2").arg(Points[0].x).arg(Points[0].y);
	QString point2 = Points.size()  < 2 ? "" : QString("%1, %2").arg(Points[1].x).arg(Points[1].y);
	QString point3 = Points.size()  < 3 ? "" : QString("%1, %2").arg(Points[2].x).arg(Points[2].y);
	QString point4 = Points.size()  < 4 ? "" : QString("%1, %2").arg(Points[3].x).arg(Points[3].y);

	//显示特征值
	ui.LineEditFeatureX->clear();
	ui.LineEditFeatureX->setText(point1);
	ui.LineEditFeatureY->clear();
	ui.LineEditFeatureY->setText(point2);
	ui.LineEditFeatureArea->clear();
	ui.LineEditFeatureArea->setText(point3);
	ui.LineEditFeatureAngle->clear();
	ui.LineEditFeatureAngle->setText(point4);
}


 void uppercomputer::startPoseTimer()
 {
	 if (ui.ButtonDisplayPose->text() == tr("DisplayPose"))
	 {
		 QString IP = "88.88.88.89";
		 int port = 30003;
		 socket->abort();
		 socket->connectToHost(IP, port);
		 posetimer->start(50);
		 if (!socket->waitForConnected(3))
		 {
			 qDebug() << "Connection failed!";
			 QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit("Robot not connected!"));
			 return;
		 }
		 qDebug() << "Connect successfully!";

		 ui.ButtonDisplayPose->setText("ClosePose");
	 }
	 else
	 {
		 socket->disconnectFromHost();
		 posetimer->stop();
		 ui.ButtonDisplayPose->setText("DisplayPose");
		 ui.LineEditPoseR0->clear();
		 ui.LineEditPoseR1->clear();
		 ui.LineEditPoseR2->clear();
		 ui.LineEditPoseR3->clear();
		 ui.LineEditPoseR4->clear();
		 ui.LineEditPoseR5->clear();
	 }
 }

 void uppercomputer::readyToRead()
 {
	 connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadData()));
 }

 void uppercomputer::socketReadData()
 {
	 QByteArray buffer;
	 int jointposeaddress = 252;
	 buffer = socket->readAll();
	 char *buff = buffer.data();

	 if (!buffer.isEmpty())
	 {
		 //ui.TextEditDebug->clear();
		 //ui.TextEditDebug->appendPlainText("reading pose!");
		 for (int i = 0; i<6; i++)
		 {
			 char temp[8];
			 double temppose;
			 for (int j = 0; j<8; j++)
			 {
				 temp[j] = buff[jointposeaddress + 8 * i + 7 - j];
			 }
			 memcpy(&temppose, temp, sizeof(temppose));
			 posevector[i]=temppose;
		 }
	 }

	 disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadData()));

	 ui.LineEditPoseR0->clear();
	 ui.LineEditPoseR0->setText(QString("%1").arg(posevector[0]));
	 ui.LineEditPoseR1->clear();
	 ui.LineEditPoseR1->setText(QString("%1").arg(posevector[1]));
	 ui.LineEditPoseR2->clear();
	 ui.LineEditPoseR2->setText(QString("%1").arg(posevector[2]));
	 ui.LineEditPoseR3->clear();
	 ui.LineEditPoseR3->setText(QString("%1").arg(posevector[3]));
	 ui.LineEditPoseR4->clear();
	 ui.LineEditPoseR4->setText(QString("%1").arg(posevector[4]));
	 ui.LineEditPoseR5->clear();
	 ui.LineEditPoseR5->setText(QString("%1").arg(posevector[5]));
 }


 void uppercomputer::startMoveTimer()
 {
	 if (ui.ButtonMove->text() == tr("Move"))
	 { 
		 int port = 8000;
		 if (!server->listen(QHostAddress::Any, port))
		 { 
			 ui.TextEditDebug->appendPlainText(server->errorString());
			 return;
		 }
		 ui.ButtonMove->setText("Stop");
	 }
	 else
	 {
		 if (socket->state() == QAbstractSocket::ConnectedState)
		 {
			 socket->disconnectFromHost();
		 }
		 server->close();
		 movetimer->stop();
		 ui.ButtonMove->setText("Move");
		 ui.TextEditDebug->clear();
	 }
 }

 void uppercomputer::serverNewConnect()
 {
	 //获取客户端连接  
	 QObject::connect(movesocket, SIGNAL(disconnected()), this, SLOT(moveSocketDisconnected()));
	 movesocket = server->nextPendingConnection();
	 movetimer->start(33);
	 counter = 0;
	 ui.TextEditDebug->appendPlainText("A client connected!");
 }

 void uppercomputer::jointMove()
 {
	 if (counter > 30)
		 movetimer->stop();
	 QString pointstr = "(0.30, -1.36, -1.84, -1.51, 1.57, -3.40)\n";
	 int pointcounter = 30 + 5 * counter;
	 QString substr = QString("%1").arg(pointcounter);
	 QString point = pointstr.replace(3, 2, substr);
	 //ui.TextEditDebug->clear();
	 ui.TextEditDebug->appendPlainText("move to " + point);
	 movesocket->write(point.toLatin1());
	 counter++;
 }

 void uppercomputer::moveSocketDisconnected()
 {
	 movetimer->stop();
 }

 uppercomputer::~uppercomputer()
 {
	 //delete &ui;
	 delete cameratimer;
	 delete posetimer;
	 delete fpstimer;
	 delete socket;
	 delete camera;
	 delete onistream;
	 delete movetimer;
	 delete movesocket;
	 delete server;
 }