#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	deleteLog();
	camera = new Camera();
	robot = new RobotControl();
	processThread = new ProcessThread();
	init = new RobotInitialization();

	fpstimer = new cvflann::StartStopTimer;

	try {
		camera->initial();
	}
	catch (CameraException& camexc)
	{
		//QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
	}

	try {
		//robot->initial();
	}
	catch (RobotException& robotexc)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}


	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(ui.ButtonTrack, SIGNAL(clicked()), init, SLOT(startInitialize()));

	connect(timer, SIGNAL(timeout()), this, SLOT(displayCamera()));
	connect(timer, SIGNAL(timeout()), this, SLOT(displayPose()));
	connect(init, SIGNAL(initReady(Mat, Mat, Mat, Mat)),\
		processThread, SLOT(initThread(Mat, Mat, Mat, Mat)), Qt::QueuedConnection);

	//connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT())

	connect(this, SIGNAL(sendPose(Mat)), processThread, SLOT(receivePose(Mat)), Qt::QueuedConnection);
	connect(this, SIGNAL(sendFeature(Mat)), processThread, SLOT(receiveFeature(Mat)), Qt::QueuedConnection);
	connect(processThread, SIGNAL(sendPose(Mat)), this, SLOT(receivePose(Mat)), Qt::QueuedConnection);
}

void uppercomputer::startTimer()
{
	if (ui.ButtonOpenCam->text() == tr("start"))
	{
		timer->start(50);

		ui.ButtonOpenCam->setText("stop");
	}
	else
	{
		timer->stop();
		ui.ButtonOpenCam->setText("start");
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

	Mat originimg, featureimg;
	QImage qoriginimg, qfeatureimg;
	vector<double> Points;

	fpstimer->start();
	try
	{
		originimg = camera->getOriginImg();
		featureimg = camera->getFeatureImg();
		Points = camera->getFeaturePoints();
	}
	catch (CameraException& camexc)
	{
		//QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
		//exit(-1);
		return;
	}


	vector<double> posevector = robot->getJointAngle();

	emit sendPose(Mat(posevector).t());


	fpstimer->stop();
	fps = 1.0 / fpstimer->value;
	fpstimer->reset();

	QString fpsstr = QString("%1").arg(fps);

	ui.FPSLineEdit->clear();
	ui.FPSLineEdit->setText(fpsstr);


	qoriginimg = QImage((const uchar*)(originimg.data), originimg.cols, originimg.rows, originimg.cols*originimg.channels(), QImage::Format_RGB888);
	qfeatureimg = QImage((const uchar*)(featureimg.data), featureimg.cols, featureimg.rows, featureimg.cols*featureimg.channels(), QImage::Format_RGB888);

	ui.LabelCamera->clear();
	ui.LabelFeature->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(qoriginimg));
	ui.LabelFeature->setPixmap(QPixmap::fromImage(qfeatureimg));
	ui.LabelCamera->show();
	ui.LabelFeature->show();

	QString point1 = Points.size()  < 1 ? "" : QString("%1, %2").arg(Points[0]).arg(Points[1]);
	QString point2 = Points.size()  < 2 ? "" : QString("%1, %2").arg(Points[2]).arg(Points[3]);
	QString point3 = Points.size()  < 3 ? "" : QString("%1, %2").arg(Points[4]).arg(Points[5]);
	QString point4 = Points.size()  < 4 ? "" : QString("%1, %2").arg(Points[6]).arg(Points[7]);

	//ÏÔÊ¾ÌØÕ÷Öµ
	ui.LineEditFeatureX->clear();
	ui.LineEditFeatureX->setText(point1);
	ui.LineEditFeatureY->clear();
	ui.LineEditFeatureY->setText(point2);
	ui.LineEditFeatureArea->clear();
	ui.LineEditFeatureArea->setText(point3);
	ui.LineEditFeatureAngle->clear();
	ui.LineEditFeatureAngle->setText(point4);
}


 void uppercomputer::displayPose()
 {
	 vector<double> posevector = robot->getJointAngle();

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

 void uppercomputer::receivePose(Mat pose)
 {
	 robot->movej(vector<double>{pose.at<double>(0), pose.at<double>(1),
	 pose.at<double>(2), pose.at<double>(3), pose.at<double>(4), pose.at<double>(5)});

	 vector<double> Points = camera->getFeaturePoints();
	 emit sendFeature(Mat(Points));
 }

 uppercomputer::~uppercomputer()
 {
	 //delete &ui;
	 delete timer;
	 delete fpstimer;
	 delete camera;
	 delete robot;
 }