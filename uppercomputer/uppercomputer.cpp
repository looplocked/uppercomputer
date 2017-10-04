#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(showImage()));
	connect(ui.opencam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(ui.closecam, SIGNAL(clicked()), this, SLOT(closeCam()));
}

 void uppercomputer::showImage()
{
	Mat rgb;
	QImage img;
	int key = 0;

	Mat frame = cam.getImage(oniColorStreamparam);
	cv::cvtColor(frame, rgb, CV_BGR2RGB);
	img = QImage((const uchar*)(rgb.data), rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);

	ui.LabelCamera->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(img));
	ui.LabelCamera->resize(ui.LabelCamera->pixmap()->size());
	ui.LabelCamera->show();
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