#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	camera = new CameraDisplay();
	robot = new RobotControl();
	processThread = new ProcessThread();

	fpstimer = new cvflann::StartStopTimer;


	try {
		camera->initialize();
	}
	catch (CameraException& camexc)
	{
		//QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
	}

	try {
		robot->poseReadInitialize();
	}
	catch (RobotException& robotexc)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}

	try {
		robot->PoseSendInitialize();
	}
	catch (RobotException& robotexc)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(robotexc.what()));
	}

	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(timer, SIGNAL(timeout()), this, SLOT(displayCamera()));
	connect(timer, SIGNAL(timeout()), this, SLOT(displayPose()));

	//connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT())

	connect(this, SIGNAL(sendData(vector<double> pose, vector<Point> feature)), processThread, SLOT(receiveData(vector<double> newpose, vector<Point> newfeature)));
	connect(processThread, SIGNAL(sendPose(vector<double> pose)), this, SLOT(vector<double> pose));
}

void uppercomputer::startTimer()
{
	if (ui.ButtonOpenCam->text() == tr("start"))
	{
		timer->start(33);

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

	Mat srcimg, originimg;
	QImage qoriginimg, qfeatureimg;

	fpstimer->start();
	try
	{
		srcimg = camera->getImage();
	}
	catch (CameraException& camexc)
	{
		//QMessageBox::information(this, QString::fromLocal8Bit("Warning!"), QString::fromLocal8Bit(camexc.what()));
		//exit(-1);
		return;
	}

	originimg = mirrorMap(srcimg);


	vector<Point> Points;
	Mat drawImg2 = processAndGetFeature(originimg, Points);

	vector<double> posevector = robot->readPose();

	emit sendData(posevector, Points);


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
	 vector<double> posevector = robot->readPose();

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

 void uppercomputer::receiveData(vector<double> pose)
 {
	 robot->jointMove(pose);
 }


 uppercomputer::~uppercomputer()
 {
	 //delete &ui;
	 delete timer;
	 delete fpstimer;
	 delete camera;
	 delete robot;
 }