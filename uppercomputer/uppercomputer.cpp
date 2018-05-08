#include "uppercomputer.h"
#include "helper.h"

uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	counter = 0;

	cameratimer = new QTimer(this);
	posetimer = new QTimer(this);
	movetimer = new QTimer(this);

	camera = new CameraDisplay();
	device = new Device();
	onistream = new VideoStream();
	fpstimer = new cvflann::StartStopTimer;

	posevector = { 0, 0, 0, 0, 0, 0 };
	feature = { 0, 0, 0, 0 };

#if 0
	ls = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);//或者两种LSD算法，这边用的是standard的
#else
	ls = cv_::createLineSegmentDetector(cv_::LSD_REFINE_NONE);
#endif

	socket = new QTcpSocket(this);
	server = new QTcpServer(this);
	//movesocket = new QTcpSocket(this);

	camera->initialize(*device, *onistream);

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

	Mat srcimg, gray, featureimg;
	Mat originimg, map_x, map_y;
	QImage qoriginimg, qfeatureimg;

	fpstimer->start();

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

	remap(srcimg, originimg, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	cv::cvtColor(originimg, gray, COLOR_RGB2GRAY);
	cv::Mat img_binary = gray.clone();
	threshold(img_binary, img_binary, 240, 255, CV_THRESH_BINARY);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(16, 16));
	morphologyEx(img_binary, img_binary, cv::MORPH_OPEN, element);

	cv::Mat showbinary = img_binary.clone();

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(img_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	int maxArea = 0;
	cv::Rect r1;
	CvBox2D r2;

	std::vector<cv::Rect> rects;
	std::vector<cv::Rect> rects_all;
	for (int i = 0; i < contours.size(); i++)
	{
		maxArea = contours[i].size();
		r2 = cv::minAreaRect(contours[i]);
		r1 = cv::boundingRect(contours[i]);
		rects_all.push_back(r1);
		if (r1.area() < 10000 || r1.area() > 50000)
		{
			continue;
		}

		rects.push_back(r1);
	}

	int max_dis = 999;
	cv::Rect r(0, 0, 0, 0);
	cv::Point P1, P2;
	P1.x = originimg.cols*0.5;
	P1.y = originimg.rows*0.5;

	for (int i = 0; i < rects.size(); i++)
	{
		P2.x = rects[i].x + 0.5*rects[i].width;
		P2.y = rects[i].y + 0.5*rects[i].height;

		double distance;
		distance = powf((P1.x - P2.x), 2) + powf((P1.y - P2.y), 2);
		distance = sqrtf(distance);

		if (distance < max_dis)
		{
			max_dis = distance;
			r = rects[i];
		}
	}

	int max_all = 0;
	if (r.area() == 0)
	{
		for (int i = 0; i < rects_all.size(); i++)
		{
			if (rects_all[i].area() > max_all)
			{
				max_all = rects_all[i].area();
				r = rects_all[i];
			}
		}
	}

	//感兴趣区域扩展
	if (r.area() == 0)
	{
		r = cv::Rect(0, 0, 639, 479);
	}
	else
	{
		/*r.x -= 10;
		r.y -= 10;
		r.width += 20;
		r.height += 20;*/
	}

	std::vector<cv::Vec4f> lines_std;
	lines_std.reserve(1000);
	ls->detect(gray(r), lines_std);//这里把检测到的直线线段都存入了lines_std中，4个float的值，分别为起止点的坐标

								   //去除干扰线段
	findPrimaryAngle(lines_std);
	//*****************************

	cv::Mat drawImg = originimg.clone();
	cv::Mat drawImg2 = originimg.clone();
	//ls->drawSegments(drawImg, lines_std);
	//imshow("2", drawImg);

	std::vector<cv::Point> Points;
	for (int i = 0; i < lines_std.size(); i++)
	{
		cv::Point p1, p2;
		p1 = cv::Point(lines_std[i][0] + r.x, lines_std[i][1] + r.y);
		p2 = cv::Point(lines_std[i][2] + r.x, lines_std[i][3] + r.y);

		Points.push_back(p1);
		Points.push_back(p2);
	}

	//条件滤波 暂时关闭
	//selectPoints(Points);
	//******************************

	//画图
	for (int i = 0; i < Points.size(); i++)
	{
		circle(drawImg2, Points[i], 5, Scalar(0, 0, 255), 2, 18);
		int j = i == Points.size() - 1 ? 0 : i + 1;
		line(drawImg2, Points[i], Points[j], Scalar(255, 0, 0), 2, 8);
	}

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