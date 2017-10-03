#include "uppercomputer.h"

Device deviceparam;
VideoStream oniColorStreamparam;
CameraDisplay cam;

uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(disCam));
}

void uppercomputer::initCam()
{
	timer->start(33);
	cam.initialize(deviceparam, oniColorStreamparam);
}


void uppercomputer::disCam()
{
	Mat frame = cam.getImage(oniColorStreamparam);
	Mat rgb;
	QImage img;
	cv::cvtColor(frame, rgb, CV_BGR2RGB);
	img = QImage((const uchar*)(rgb.data), rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);

	//ui.LabelCamera->clear();
	ui.LabelCamera->setPixmap(QPixmap::fromImage(img));
	ui.LabelCamera->resize(ui.LabelCamera->pixmap()->size());
	ui.LabelCamera->show();
}