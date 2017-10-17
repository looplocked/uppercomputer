#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(showImage()));
	connect(timer, SIGNAL(timeout()), this, SLOT(disFeature()));
	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), this, SLOT(closeCam()));
}

 void uppercomputer::showImage()
{
	Mat rgb, edge, feature;
	QImage originimg, featureimg;

	Mat frame = cam.getImage(oniColorStreamparam);
	cv::cvtColor(frame, edge, COLOR_RGB2GRAY);
	threshold(edge, edge, 130, 255, 3);
	medianBlur(edge, edge, 7);
	Canny(edge, edge, 3, 9, 3);
	originimg = QImage((const uchar*)(frame.data), frame.cols, frame.rows, frame.cols*frame.channels(), QImage::Format_RGB888);
	featureimg = QImage((const uchar*)(edge.data), edge.cols, edge.rows, edge.cols*edge.channels(), QImage::Format_Indexed8);

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
	 cam.initialize(deviceparam, oniColorStreamparam);
	 timer->start(33);
 }

 void uppercomputer::closeCam()
 {
	 timer->stop();
	 ui.LabelCamera->clear();
 }

 void uppercomputer::disFeature()
 {
	 Mat srcImage, binaryImage;
	 QImage originimg, featureimg;

	 srcImage = cam.getImage(oniColorStreamparam);
	 cv::cvtColor(srcImage, srcImage, COLOR_RGB2GRAY);
	 threshold(srcImage, binaryImage, 130, 255, 3);
	 medianBlur(binaryImage, binaryImage, 7);

	 vector<vector<Point>> contours;
	 vector<Vec4i> hierarchy;
	 findContours(binaryImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	 vector<Point> contour = contours[0];
	 if (contours.size() > 1)
	 {
		 for (auto iter = contours.begin(); iter != contours.end(); iter++)
		 {
			 if ((*iter).size() > contour.size())
				 contour = *iter;
		 }
	 }



	 // ¼ÆËãÍ¼Ïñ¾Ø
	 Moments mu = moments(contour, false);
	 Point2f mc;
	 mc = Point2f(static_cast<float>(mu.m10 / mu.m00), static_cast<float>(mu.m01 / mu.m00));
	 RotatedRect rect = minAreaRect(contour);

	 QString x = QString("%1").arg(mc.x);
	 QString y = QString("%1").arg(mc.y);
	 QString area = QString("%1").arg(contourArea(contour));
	 QString ang = QString("%1").arg(-rect.angle);


	 ui.LineEditFeatureX->clear();
	 ui.LineEditFeatureX->setText(x);
	 ui.LineEditFeatureY->clear();
	 ui.LineEditFeatureY->setText(y);
	 ui.LineEditFeatureArea->clear();
	 ui.LineEditFeatureArea->setText(area);
	 ui.LineEditFeatureAngle->clear();
	 ui.LineEditFeatureAngle->setText(ang);
 }