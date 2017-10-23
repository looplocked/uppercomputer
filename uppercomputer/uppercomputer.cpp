#include "uppercomputer.h"



uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	cameratimer = new QTimer(this);
	posetimer = new QTimer(this);

	camera = new CameraDisplay();
	device = new Device();
	onistream = new VideoStream();

	posevector = { 0, 0, 0, 0, 0, 0 };
	feature = { 0, 0, 0, 0 };

	socket = new QTcpSocket(this);

	camera->initialize(*device, *onistream);

	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startCameraTimer()));
	connect(cameratimer, SIGNAL(timeout()), this, SLOT(displayCamera()));

	
	connect(ui.ButtonDisplayPose, SIGNAL(clicked()), this, SLOT(startPoseTimer()));
	connect(posetimer, SIGNAL(timeout()), this, SLOT(readyToRead()));

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
	Mat srcimg, temp, featureimg;
	Mat originimg, map_x, map_y;
	QImage qoriginimg, qfeatureimg;

	srcimg = camera->getImage(*onistream);
	originimg.create(srcimg.size(), srcimg.type());
	map_x.create(srcimg.size(), CV_32FC1);
	map_y.create(srcimg.size(), CV_32FC1);

	for (int j = 0; j < srcimg.rows; j++)
	{
		for (int i = 0; i < srcimg.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(srcimg.cols - i);
			map_y.at<float>(j, i) = static_cast<float>(j);
		}
	}
	//int thresholdvalue = ui.ThresholdSlider->value();
	//ui.LabelThreshold->setText(QString("%1").arg(thresholdvalue));
	remap(srcimg, originimg, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	cv::cvtColor(originimg, temp, COLOR_RGB2GRAY);
	threshold(temp, temp, 246, 255, 0);
	medianBlur(temp, featureimg, 7);


	qoriginimg = QImage((const uchar*)(originimg.data), originimg.cols, originimg.rows, originimg.cols*originimg.channels(), QImage::Format_RGB888);
	qfeatureimg = QImage((const uchar*)(featureimg.data), featureimg.cols, featureimg.rows, featureimg.cols*featureimg.channels(), QImage::Format_Indexed8);

	ui.LabelCamera->clear();
	ui.LabelFeature->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(qoriginimg));
	ui.LabelFeature->setPixmap(QPixmap::fromImage(qfeatureimg));
	ui.LabelCamera->show();
	ui.LabelFeature->show();


	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(featureimg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	vector<Point> contour = contours[0];
	if (contours.size() > 1)
	{
		for (auto iter = contours.begin(); iter != contours.end(); iter++)
		{
			if ((*iter).size() > contour.size())
				contour = *iter;
		}
	}
	//Ѱ������
	Moments mu = moments(contour, false);
	Point2f mc;
	mc = Point2f(static_cast<float>(mu.m10 / mu.m00), static_cast<float>(mu.m01 / mu.m00));

	feature[0] = mc.x;
	feature[1] = mc.y;
	feature[2] = contourArea(contour);
	RotatedRect rect = minAreaRect(contour);
	feature[3] = -rect.angle;

	QString x = QString("%1").arg(feature[0]);
	QString y = QString("%1").arg(feature[1]);
	QString area = QString("%1").arg(feature[2]);
	QString ang = QString("%1").arg(feature[3]);

	//��ʾ����ֵ
	ui.LineEditFeatureX->clear();
	ui.LineEditFeatureX->setText(x);
	ui.LineEditFeatureY->clear();
	ui.LineEditFeatureY->setText(y);
	ui.LineEditFeatureArea->clear();
	ui.LineEditFeatureArea->setText(area);
	ui.LineEditFeatureAngle->clear();
	ui.LineEditFeatureAngle->setText(ang);
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
		 if (!socket->waitForConnected(30000))
		 {
			 qDebug() << "Connection failed!";
			 return;
		 }
		 qDebug() << "Connect successfully!";

		 ui.ButtonDisplayPose->setText("ClosePose");
	 }
	 else
	 {
		 socket->disconnectFromHost();
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
		 for (int i = 0; i<6; i++)
		 {
			 char temp[8];
			 double temppose;
			 for (int j = 0; j<8; j++)
			 {
				 temp[j] = buff[jointposeaddress + 8 * i + 7 - j];
			 }
			 memcpy(&temppose, temp, sizeof(temppose));
			 posevector.push_back(temppose);
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

 uppercomputer::~uppercomputer()
 {
	 //delete &ui;
	 delete cameratimer;
	 delete posetimer;
	 delete socket;
	 delete camera;
	 delete device;
	 delete onistream;
 }