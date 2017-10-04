#pragma once
#ifndef UPPERCOMPUTER_H
#define UPPERCOMPUTER_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include "ui_uppercomputer.h"
#include "cameradisplay.h"
#include "OpenNI.h"  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

using namespace std;
using namespace cv;
using namespace openni;


class uppercomputer : public QMainWindow
{
	Q_OBJECT

public:
	uppercomputer(QWidget *parent = Q_NULLPTR);

private:
	Ui::uppercomputerClass ui;
	QTimer *timer;
	Device deviceparam;
	VideoStream oniColorStreamparam;
	CameraDisplay cam;


public slots:
    void showImage();
	void startTimer();
	void closeCam();
};



#endif