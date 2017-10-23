#include "uppercomputer.h"



uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	imagetimer = new QTimer(this);
	featuretimer = new QTimer(this);
	posetimer = new QTimer(this);

	socket = new QTcpSocket(this);

	camera = new CameraThread();
	feature = new FeatureThread();

	//qRegisterMetaType<Mat>("Mat");


	connect(imagetimer, SIGNAL(timeout()), camera, SLOT(getImage()));
	connect(camera, SIGNAL(gotAImage(Mat, Mat)), this, SLOT(showImage(Mat, Mat)), Qt::BlockingQueuedConnection);  //第五个参数很重要，需要进一步研究
	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startImageTimer()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), this, SLOT(closeCam()));
	//connect(ui.ButtonCloseCam, SIGNAL(clicked()), camera, SLOT(camera->stop()));

	connect(featuretimer, SIGNAL(timeout()), feature, SLOT(getFeature()));
	connect(feature, SIGNAL(gotAFeature(double, double, double, double)), this, SLOT(disFeature(double, double, double, double)), Qt::QueuedConnection);
	connect(ui.ButtonDisFeature, SIGNAL(clicked()), this, SLOT(startFeatureTimer()));
	connect(ui.ButtonCloseFeature, SIGNAL(clicked()), this, SLOT(closeFeature()));
	
	connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT(startPoseTimer()));
	connect(posetimer, SIGNAL(timeout()), this, SLOT(readyToRead()));

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
	 imagetimer->start(200);
 }

 void uppercomputer::startFeatureTimer()
 {
	 featuretimer->start(200);
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

	 //显示特征值
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

 void uppercomputer::startPoseTimer()
 {
	 if (ui.ButtonDisplayPose->text() == tr("DisplayPose"))
	 {
		 QString IP = "88.88.88.89";
		 int port = 30003;
		 socket->abort();
		 socket->connectToHost(IP, port);
		 posetimer->start(200);
		 if (!socket->waitForConnected(30000))
		 {
			 qDebug() << "Connection failed!";
			 return;
		 }
		 qDebug() << "Connect successfully!";

		 ui.ButtonCloseCam->setText("cancel");
	 }
	 else
	 {
		 socket->disconnectFromHost();
		 ui.ButtonDisplayPose->setText("DisplayPose");
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
	 vector<QString> posevector;
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
				 temp[j] = buff[jointposeaddress + 8 * i + 7 - j];
			 }
			 memcpy(&temppose, temp, sizeof(temppose));
			 posevector.push_back(QString("%1").arg(temppose));
		 }
	 }

	 disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadData()));

	 ui.LineEditPoseR0->clear();
	 ui.LineEditPoseR0->setText(posevector[0]);
	 ui.LineEditPoseR1->clear();
	 ui.LineEditPoseR1->setText(posevector[1]);
	 ui.LineEditPoseR2->clear();
	 ui.LineEditPoseR2->setText(posevector[2]);
	 ui.LineEditPoseR3->clear();
	 ui.LineEditPoseR3->setText(posevector[3]);
	 ui.LineEditPoseR4->clear();
	 ui.LineEditPoseR4->setText(posevector[4]);
	 ui.LineEditPoseR5->clear();
	 ui.LineEditPoseR5->setText(posevector[5]);
 }

 //void uppercomputer::socketDisconnected()
// {
//	 qDebug() << "Disconnected!";
 //}