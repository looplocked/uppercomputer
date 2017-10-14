#include "uppercomputer.h"


uppercomputer::uppercomputer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(showImage()));
	connect(ui.ButtonOpenCam, SIGNAL(clicked()), this, SLOT(startTimer()));
	connect(ui.ButtonCloseCam, SIGNAL(clicked()), this, SLOT(closeCam()));
}

 void uppercomputer::showImage()
{
	Mat rgb, edge, feature;
	QImage originimg, featureimg;
	int key = 0;

	Mat frame = cam.getImage(oniColorStreamparam);
	cv::cvtColor(frame, edge, COLOR_RGB2GRAY);
	threshold(edge, edge, 100, 255, 3);
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