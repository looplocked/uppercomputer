#include "uppercomputer.h"



uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	imagetimer = new QTimer(this);
	featuretimer = new QTimer(this);
	//server = new QTcpServer(this);
	camera = new CameraThread();
	feature = new FeatureThread();

	//qRegisterMetaType<Mat>("Mat");


	connect(imagetimer, SIGNAL(timeout()), camera, SLOT(getImage()));
	connect(camera, SIGNAL(gotAImage(Mat, Mat)), this, SLOT(showImage(Mat, Mat)), Qt::BlockingQueuedConnection);
	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startImageTimer()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), this, SLOT(closeCam()));
	//connect(ui.ButtonCloseCam, SIGNAL(clicked()), camera, SLOT(camera->stop()));

	connect(featuretimer, SIGNAL(timeout()), feature, SLOT(getFeature()));
	connect(feature, SIGNAL(gotAFeature(double, double, double, double)), this, SLOT(disFeature(double, double, double, double)), Qt::QueuedConnection);
	connect(ui.ButtonDisFeature, SIGNAL(clicked()), this, SLOT(startFeatureTimer()));
	connect(ui.ButtonCloseFeature, SIGNAL(clicked()), this, SLOT(closeFeature()));
	
	//connect(server, &QTcpServer::newConnection, this, &uppercomputer::serverNewConnect);
	//connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT(disPose()));
}

 void uppercomputer::showImage(Mat originimg, Mat featureimg)
{
	QImage qoriginimg, qfeatureimg;


	qoriginimg = QImage((const uchar*)(originimg.data), originimg.cols, originimg.rows, originimg.cols*originimg.channels(), QImage::Format_RGB888);
	qfeatureimg = QImage((const uchar*)(featureimg.data), featureimg.cols, featureimg.rows, featureimg.cols*featureimg.channels(), QImage::Format_Indexed8);

	ui.LabelCamera->clear();
	ui.LabelFeature->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(qoriginimg));
	ui.LabelFeature->setPixmap(QPixmap::fromImage(qfeatureimg));
	ui.LabelCamera->show();
	ui.LabelFeature->show();
}

 void uppercomputer::startImageTimer()
 {
	 imagetimer->start(50);
 }

 void uppercomputer::startFeatureTimer()
 {
	 featuretimer->start(50);
 }

 void uppercomputer::closeCam()
 {
	 imagetimer->stop();
	 ui.LabelCamera->clear();
	 ui.LabelFeature->clear();
 }

 void uppercomputer::disFeature(double featurex, double featurey, double featurearea, double featureang)
 {

	 QString x = QString("%1").arg(featurex);
	 QString y = QString("%1").arg(featurey);
	 QString area = QString("%1").arg(featurearea);
	 QString ang = QString("%1").arg(featureang);

	 //ÏÔÊ¾ÌØÕ÷Öµ
	 ui.LineEditFeatureX->clear();
	 ui.LineEditFeatureX->setText(x);
	 ui.LineEditFeatureY->clear();
	 ui.LineEditFeatureY->setText(y);
	 ui.LineEditFeatureArea->clear();
	 ui.LineEditFeatureArea->setText(area);
	 ui.LineEditFeatureAngle->clear();
	 ui.LineEditFeatureAngle->setText(ang);
 }

 void uppercomputer::closeFeature()
 {
	 featuretimer->stop();
	 ui.LineEditFeatureX->clear();
	 ui.LineEditFeatureY->clear();
	 ui.LineEditFeatureArea->clear();
	 ui.LineEditFeatureAngle->clear();
 }

 //void uppercomputer::disPose()
 //{
//	 if (ui.ButtonDisplayPose->text() == tr("DisplayPose"))
//	 {
//		 int port = 8000;
//		 if (!server->listen(QHostAddress::Any, port))
//		 {
//			 qDebug() << server->errorString();
//			 return;
//		 }
//		 ui.ButtonDisplayPose->setText("CancelDisplay");
//		 qDebug() << "Listen successfully!";
//	 }
//	 else
//	 {
//		 if (socket->state() == QAbstractSocket::ConnectedState)
//		 {
//			 socket->disconnectFromHost();
//		 }
//		 server->close();
//	 }
// }

 //void uppercomputer::serverNewConnect()
//{
//	 socket = server->nextPendingConnection();
//	 connect(socket, &QTcpSocket::readyRead, this, &uppercomputer::socketReadData);
//	 connect(socket, &QTcpSocket::disconnected, this, &uppercomputer::socketDisconnected);
//	 qDebug() << "A Client connect!";
 //}

 //void uppercomputer::socketReadData()
 //{
//	 QByteArray buffer;
//	 buffer = socket->readAll();
//	 if (!buffer.isEmpty())
//	 {
//		 QString pose;
//		 pose = tr(buffer);
//		 ui.LineEditPoseX->clear();
//		 ui.LineEditPoseX->setText(pose);
//		 ui.LineEditPoseY->clear();
//		 ui.LineEditPoseY->setText(pose);
//		 ui.LineEditPoseZ->clear();
//		 ui.LineEditPoseZ->setText(pose);
//		 ui.LineEditPoseRx->clear();
//		 ui.LineEditPoseRx->setText(pose);
//		 ui.LineEditPoseRy->clear();
//		 ui.LineEditPoseRy->setText(pose);
//		 ui.LineEditPoseRz->clear();
//		 ui.LineEditPoseRz->setText(pose);
//	 }
 //}

 //void uppercomputer::socketDisconnected()
// {
//	 qDebug() << "Disconnected!";
 //}