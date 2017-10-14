/********************************************************************************
** Form generated from reading UI file 'uppercomputer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPPERCOMPUTER_H
#define UI_UPPERCOMPUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uppercomputerClass
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *lineEditPoseX;
    QLabel *LabelPoseY;
    QLineEdit *lineEditPoseY;
    QLabel *LabelPoseZ;
    QLineEdit *lineEditPoseZ;
    QLabel *LabelPoseRx;
    QLineEdit *lineEditPoseRx;
    QLabel *LabelPoseRy;
    QLineEdit *lineEditPoseRy;
    QLabel *LabelPoseRz;
    QLineEdit *lineEditPoseRz;
    QLabel *LabelPoseX;
    QPushButton *ButtonDisplayPose;
    QPushButton *ButtonDisFeature;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *LabelFeatureX;
    QLineEdit *lineEditFeatureZ;
    QLabel *LabelFeatureY;
    QLineEdit *lineEditFeatureY;
    QLabel *LabelFeatureArea;
    QLineEdit *lineEditFeatureArea;
    QLabel *LabelFeatureAngle;
    QLineEdit *lineEditFeatureAngle;
    QPushButton *ButtonTrack;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelCamera;
    QLabel *LabelFeature;
    QWidget *widget2;
    QVBoxLayout *verticalLayout;
    QPushButton *ButtonOpenCam;
    QPushButton *ButtonCloseCam;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *uppercomputerClass)
    {
        if (uppercomputerClass->objectName().isEmpty())
            uppercomputerClass->setObjectName(QStringLiteral("uppercomputerClass"));
        uppercomputerClass->resize(1238, 704);
        centralWidget = new QWidget(uppercomputerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(90, 390, 161, 255));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayout->setHorizontalSpacing(6);
        formLayout->setVerticalSpacing(20);
        formLayout->setContentsMargins(0, 0, 0, 0);
        lineEditPoseX = new QLineEdit(formLayoutWidget);
        lineEditPoseX->setObjectName(QStringLiteral("lineEditPoseX"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditPoseX);

        LabelPoseY = new QLabel(formLayoutWidget);
        LabelPoseY->setObjectName(QStringLiteral("LabelPoseY"));

        formLayout->setWidget(1, QFormLayout::LabelRole, LabelPoseY);

        lineEditPoseY = new QLineEdit(formLayoutWidget);
        lineEditPoseY->setObjectName(QStringLiteral("lineEditPoseY"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditPoseY);

        LabelPoseZ = new QLabel(formLayoutWidget);
        LabelPoseZ->setObjectName(QStringLiteral("LabelPoseZ"));

        formLayout->setWidget(2, QFormLayout::LabelRole, LabelPoseZ);

        lineEditPoseZ = new QLineEdit(formLayoutWidget);
        lineEditPoseZ->setObjectName(QStringLiteral("lineEditPoseZ"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPoseZ);

        LabelPoseRx = new QLabel(formLayoutWidget);
        LabelPoseRx->setObjectName(QStringLiteral("LabelPoseRx"));

        formLayout->setWidget(3, QFormLayout::LabelRole, LabelPoseRx);

        lineEditPoseRx = new QLineEdit(formLayoutWidget);
        lineEditPoseRx->setObjectName(QStringLiteral("lineEditPoseRx"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditPoseRx);

        LabelPoseRy = new QLabel(formLayoutWidget);
        LabelPoseRy->setObjectName(QStringLiteral("LabelPoseRy"));

        formLayout->setWidget(4, QFormLayout::LabelRole, LabelPoseRy);

        lineEditPoseRy = new QLineEdit(formLayoutWidget);
        lineEditPoseRy->setObjectName(QStringLiteral("lineEditPoseRy"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditPoseRy);

        LabelPoseRz = new QLabel(formLayoutWidget);
        LabelPoseRz->setObjectName(QStringLiteral("LabelPoseRz"));

        formLayout->setWidget(5, QFormLayout::LabelRole, LabelPoseRz);

        lineEditPoseRz = new QLineEdit(formLayoutWidget);
        lineEditPoseRz->setObjectName(QStringLiteral("lineEditPoseRz"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditPoseRz);

        LabelPoseX = new QLabel(formLayoutWidget);
        LabelPoseX->setObjectName(QStringLiteral("LabelPoseX"));
        LabelPoseX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, LabelPoseX);

        ButtonDisplayPose = new QPushButton(centralWidget);
        ButtonDisplayPose->setObjectName(QStringLiteral("ButtonDisplayPose"));
        ButtonDisplayPose->setGeometry(QRect(130, 340, 75, 23));
        ButtonDisFeature = new QPushButton(centralWidget);
        ButtonDisFeature->setObjectName(QStringLiteral("ButtonDisFeature"));
        ButtonDisFeature->setGeometry(QRect(440, 340, 75, 23));
        formLayoutWidget_2 = new QWidget(centralWidget);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(400, 420, 160, 172));
        formLayout_3 = new QFormLayout(formLayoutWidget_2);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_3->setVerticalSpacing(30);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        LabelFeatureX = new QLabel(formLayoutWidget_2);
        LabelFeatureX->setObjectName(QStringLiteral("LabelFeatureX"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, LabelFeatureX);

        lineEditFeatureZ = new QLineEdit(formLayoutWidget_2);
        lineEditFeatureZ->setObjectName(QStringLiteral("lineEditFeatureZ"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lineEditFeatureZ);

        LabelFeatureY = new QLabel(formLayoutWidget_2);
        LabelFeatureY->setObjectName(QStringLiteral("LabelFeatureY"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, LabelFeatureY);

        lineEditFeatureY = new QLineEdit(formLayoutWidget_2);
        lineEditFeatureY->setObjectName(QStringLiteral("lineEditFeatureY"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lineEditFeatureY);

        LabelFeatureArea = new QLabel(formLayoutWidget_2);
        LabelFeatureArea->setObjectName(QStringLiteral("LabelFeatureArea"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, LabelFeatureArea);

        lineEditFeatureArea = new QLineEdit(formLayoutWidget_2);
        lineEditFeatureArea->setObjectName(QStringLiteral("lineEditFeatureArea"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEditFeatureArea);

        LabelFeatureAngle = new QLabel(formLayoutWidget_2);
        LabelFeatureAngle->setObjectName(QStringLiteral("LabelFeatureAngle"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, LabelFeatureAngle);

        lineEditFeatureAngle = new QLineEdit(formLayoutWidget_2);
        lineEditFeatureAngle->setObjectName(QStringLiteral("lineEditFeatureAngle"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, lineEditFeatureAngle);

        ButtonTrack = new QPushButton(centralWidget);
        ButtonTrack->setObjectName(QStringLiteral("ButtonTrack"));
        ButtonTrack->setGeometry(QRect(780, 400, 311, 141));
        QFont font;
        font.setPointSize(20);
        ButtonTrack->setFont(font);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(430, 10, 721, 20));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(11);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(430, 50, 721, 231));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        LabelCamera = new QLabel(widget1);
        LabelCamera->setObjectName(QStringLiteral("LabelCamera"));
        LabelCamera->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(LabelCamera);

        LabelFeature = new QLabel(widget1);
        LabelFeature->setObjectName(QStringLiteral("LabelFeature"));
        LabelFeature->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(LabelFeature);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(140, 80, 77, 148));
        verticalLayout = new QVBoxLayout(widget2);
        verticalLayout->setSpacing(100);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ButtonOpenCam = new QPushButton(widget2);
        ButtonOpenCam->setObjectName(QStringLiteral("ButtonOpenCam"));

        verticalLayout->addWidget(ButtonOpenCam);

        ButtonCloseCam = new QPushButton(widget2);
        ButtonCloseCam->setObjectName(QStringLiteral("ButtonCloseCam"));

        verticalLayout->addWidget(ButtonCloseCam);

        uppercomputerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(uppercomputerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1238, 21));
        uppercomputerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(uppercomputerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        uppercomputerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(uppercomputerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        uppercomputerClass->setStatusBar(statusBar);

        retranslateUi(uppercomputerClass);

        QMetaObject::connectSlotsByName(uppercomputerClass);
    } // setupUi

    void retranslateUi(QMainWindow *uppercomputerClass)
    {
        uppercomputerClass->setWindowTitle(QApplication::translate("uppercomputerClass", "uppercomputer", Q_NULLPTR));
        LabelPoseY->setText(QApplication::translate("uppercomputerClass", "Y:", Q_NULLPTR));
        LabelPoseZ->setText(QApplication::translate("uppercomputerClass", "Z:", Q_NULLPTR));
        LabelPoseRx->setText(QApplication::translate("uppercomputerClass", "RX:", Q_NULLPTR));
        LabelPoseRy->setText(QApplication::translate("uppercomputerClass", "RY:", Q_NULLPTR));
        LabelPoseRz->setText(QApplication::translate("uppercomputerClass", "RZ:", Q_NULLPTR));
        LabelPoseX->setText(QApplication::translate("uppercomputerClass", "X:", Q_NULLPTR));
        ButtonDisplayPose->setText(QApplication::translate("uppercomputerClass", "DisplayPose", Q_NULLPTR));
        ButtonDisFeature->setText(QApplication::translate("uppercomputerClass", "DisFeature", Q_NULLPTR));
        LabelFeatureX->setText(QApplication::translate("uppercomputerClass", "X:", Q_NULLPTR));
        LabelFeatureY->setText(QApplication::translate("uppercomputerClass", "Y:", Q_NULLPTR));
        LabelFeatureArea->setText(QApplication::translate("uppercomputerClass", "Area:", Q_NULLPTR));
        LabelFeatureAngle->setText(QApplication::translate("uppercomputerClass", "Angle:", Q_NULLPTR));
        ButtonTrack->setText(QApplication::translate("uppercomputerClass", "Track", Q_NULLPTR));
        label->setText(QApplication::translate("uppercomputerClass", "original image", Q_NULLPTR));
        label_3->setText(QApplication::translate("uppercomputerClass", "feature image", Q_NULLPTR));
        LabelCamera->setText(QApplication::translate("uppercomputerClass", "camera", Q_NULLPTR));
        LabelFeature->setText(QApplication::translate("uppercomputerClass", "binary", Q_NULLPTR));
        ButtonOpenCam->setText(QApplication::translate("uppercomputerClass", "OpenCam", Q_NULLPTR));
        ButtonCloseCam->setText(QApplication::translate("uppercomputerClass", "closecam", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class uppercomputerClass: public Ui_uppercomputerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPPERCOMPUTER_H
