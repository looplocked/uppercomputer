#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
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

private slots:
    //void initCam();
	//void disCam();
};
