#include "uppercomputer.h"


Mat g_originimg;
Mat g_featureimg;
Device g_deviceparam;
VideoStream g_oniColorStreamparam;
double g_posex=0, g_posey=0, g_posez=0, g_poserx=0, g_posery=0, g_poserz=0;
double g_featurex=0, g_featurey=0, g_featurearea=0, g_featureang=0;
CameraDisplay g_cam;
QReadWriteLock g_imagelock;
QReadWriteLock g_poselock;
QReadWriteLock g_featurelock;

uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);
	server = new QTcpServer(this);
	camera = new CameraThread();
	feature = new FeatureThread();


	connect(timer, SIGNAL(timeout()), camera, SLOT(camera->start()));
	connect(camera, SIGNAL(camera->isFinished()), this, SLOT(&uppercomputer::showImage()));
	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), this, SLOT(closeCam()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), camera, SLOT(camera->stop()));

	//connect(timer, SIGNAL(timeout()), feature, SLOT(feature->start()));
	//connect(timer, SIGNAL(timeout()), this, SLOT(disFeature()));
	
	connect(server, &QTcpServer::newConnection, this, &uppercomputer::serverNewConnect);
	connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT(disPose()));
}

 void uppercomputer::showImage()
{
	QImage originimg, featureimg;


	g_imagelock.lockForRead();
	originimg = QImage((const uchar*)(g_originimg.data), g_originimg.cols, g_originimg.rows, g_originimg.cols*g_originimg.channels(), QImage::Format_RGB888);
	featureimg = QImage((const uchar*)(g_featureimg.data), g_featureimg.cols, g_featureimg.rows, g_featureimg.cols*g_featureimg.channels(), QImage::Format_Indexed8);
	g_imagelock.unlock();

	ui.LabelCamera->clear();
	ui.LabelFeature->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(originimg));
	ui.LabelFeature->setPixmap(QPixmap::fromImage(featureimg));
	//ui.LabelCamera->resize(ui.LabelCamera->pixmap()->size());
	//ui.LabelFeature->resize(ui.LabelFeature->pixmap()->size());
	ui.LabelCamera->show();
	ui.LabelFeature->show();
}

 void uppercomputer::startTimer()
 {
	 g_cam.initialize(g_deviceparam, g_oniColorStreamparam);
	 timer->start(33);
 }

 void uppercomputer::closeCam()
 {
	 timer->stop();
	 ui.LabelCamera->clear();
 }

 void uppercomputer::disFeature()
 {

	 QString x = QString("%1").arg(g_featurex);
	 QString y = QString("%1").arg(g_featurey);
	 QString area = QString("%1").arg(g_featurearea);
	 QString ang = QString("%1").arg(g_featureang);

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

 void uppercomputer::disPose()
 {
	 if (ui.ButtonDisplayPose->text() == tr("DisplayPose"))
	 {
		 int port = 8000;
		 if (!server->listen(QHostAddress::Any, port))
		 {
			 qDebug() << server->errorString();
			 return;
		 }
		 ui.ButtonDisplayPose->setText("CancelDisplay");
		 qDebug() << "Listen successfully!";
	 }
	 else
	 {
		 if (socket->state() == QAbstractSocket::ConnectedState)
		 {
			 socket->disconnectFromHost();
		 }
		 server->close();
	 }
 }

 void uppercomputer::serverNewConnect()
 {
	 socket = server->nextPendingConnection();
	 connect(socket, &QTcpSocket::readyRead, this, &uppercomputer::socketReadData);
	 connect(socket, &QTcpSocket::disconnected, this, &uppercomputer::socketDisconnected);
	 qDebug() << "A Client connect!";
 }

 void uppercomputer::socketReadData()
 {
	 QByteArray buffer;
	 buffer = socket->readAll();
	 if (!buffer.isEmpty())
	 {
		 QString pose;
		 pose = tr(buffer);
		 ui.LineEditPoseX->clear();
		 ui.LineEditPoseX->setText(pose);
		 ui.LineEditPoseY->clear();
		 ui.LineEditPoseY->setText(pose);
		 ui.LineEditPoseZ->clear();
		 ui.LineEditPoseZ->setText(pose);
		 ui.LineEditPoseRx->clear();
		 ui.LineEditPoseRx->setText(pose);
		 ui.LineEditPoseRy->clear();
		 ui.LineEditPoseRy->setText(pose);
		 ui.LineEditPoseRz->clear();
		 ui.LineEditPoseRz->setText(pose);
	 }
 }

 void uppercomputer::socketDisconnected()
 {
	 qDebug() << "Disconnected!";
 }