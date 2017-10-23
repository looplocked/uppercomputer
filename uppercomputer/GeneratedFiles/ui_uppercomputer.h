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
#include <QtWidgets/QPlainTextEdit>
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
    QLineEdit *LineEditPoseR0;
    QLabel *LabelPoseR1;
    QLineEdit *LineEditPoseR1;
    QLabel *LabelPoseR2;
    QLineEdit *LineEditPoseR2;
    QLabel *LabelPoseR3;
    QLineEdit *LineEditPoseR3;
    QLabel *LabelPoseR4;
    QLineEdit *LineEditPoseR4;
    QLabel *LabelPoseR5;
    QLineEdit *LineEditPoseR5;
    QLabel *LabelPoseR0;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *LabelFeatureX;
    QLineEdit *LineEditFeatureX;
    QLabel *LabelFeatureY;
    QLineEdit *LineEditFeatureY;
    QLabel *LabelFeatureArea;
    QLineEdit *LineEditFeatureArea;
    QLabel *LabelFeatureAngle;
    QLineEdit *LineEditFeatureAngle;
    QPushButton *ButtonTrack;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelCamera;
    QLabel *LabelFeature;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QPushButton *ButtonOpenCam;
    QPushButton *ButtonDisplayPose;
    QPushButton *ButtonMove;
    QPlainTextEdit *TextEditDebug;
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
        LineEditPoseR0 = new QLineEdit(formLayoutWidget);
        LineEditPoseR0->setObjectName(QStringLiteral("LineEditPoseR0"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEditPoseR0);

        LabelPoseR1 = new QLabel(formLayoutWidget);
        LabelPoseR1->setObjectName(QStringLiteral("LabelPoseR1"));

        formLayout->setWidget(1, QFormLayout::LabelRole, LabelPoseR1);

        LineEditPoseR1 = new QLineEdit(formLayoutWidget);
        LineEditPoseR1->setObjectName(QStringLiteral("LineEditPoseR1"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEditPoseR1);

        LabelPoseR2 = new QLabel(formLayoutWidget);
        LabelPoseR2->setObjectName(QStringLiteral("LabelPoseR2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, LabelPoseR2);

        LineEditPoseR2 = new QLineEdit(formLayoutWidget);
        LineEditPoseR2->setObjectName(QStringLiteral("LineEditPoseR2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LineEditPoseR2);

        LabelPoseR3 = new QLabel(formLayoutWidget);
        LabelPoseR3->setObjectName(QStringLiteral("LabelPoseR3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, LabelPoseR3);

        LineEditPoseR3 = new QLineEdit(formLayoutWidget);
        LineEditPoseR3->setObjectName(QStringLiteral("LineEditPoseR3"));

        formLayout->setWidget(3, QFormLayout::FieldRole, LineEditPoseR3);

        LabelPoseR4 = new QLabel(formLayoutWidget);
        LabelPoseR4->setObjectName(QStringLiteral("LabelPoseR4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, LabelPoseR4);

        LineEditPoseR4 = new QLineEdit(formLayoutWidget);
        LineEditPoseR4->setObjectName(QStringLiteral("LineEditPoseR4"));

        formLayout->setWidget(4, QFormLayout::FieldRole, LineEditPoseR4);

        LabelPoseR5 = new QLabel(formLayoutWidget);
        LabelPoseR5->setObjectName(QStringLiteral("LabelPoseR5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, LabelPoseR5);

        LineEditPoseR5 = new QLineEdit(formLayoutWidget);
        LineEditPoseR5->setObjectName(QStringLiteral("LineEditPoseR5"));

        formLayout->setWidget(5, QFormLayout::FieldRole, LineEditPoseR5);

        LabelPoseR0 = new QLabel(formLayoutWidget);
        LabelPoseR0->setObjectName(QStringLiteral("LabelPoseR0"));
        LabelPoseR0->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, LabelPoseR0);

        formLayoutWidget_2 = new QWidget(centralWidget);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(400, 420, 160, 176));
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

        LineEditFeatureX = new QLineEdit(formLayoutWidget_2);
        LineEditFeatureX->setObjectName(QStringLiteral("LineEditFeatureX"));
        LineEditFeatureX->setEnabled(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, LineEditFeatureX);

        LabelFeatureY = new QLabel(formLayoutWidget_2);
        LabelFeatureY->setObjectName(QStringLiteral("LabelFeatureY"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, LabelFeatureY);

        LineEditFeatureY = new QLineEdit(formLayoutWidget_2);
        LineEditFeatureY->setObjectName(QStringLiteral("LineEditFeatureY"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, LineEditFeatureY);

        LabelFeatureArea = new QLabel(formLayoutWidget_2);
        LabelFeatureArea->setObjectName(QStringLiteral("LabelFeatureArea"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, LabelFeatureArea);

        LineEditFeatureArea = new QLineEdit(formLayoutWidget_2);
        LineEditFeatureArea->setObjectName(QStringLiteral("LineEditFeatureArea"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, LineEditFeatureArea);

        LabelFeatureAngle = new QLabel(formLayoutWidget_2);
        LabelFeatureAngle->setObjectName(QStringLiteral("LabelFeatureAngle"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, LabelFeatureAngle);

        LineEditFeatureAngle = new QLineEdit(formLayoutWidget_2);
        LineEditFeatureAngle->setObjectName(QStringLiteral("LineEditFeatureAngle"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, LineEditFeatureAngle);

        ButtonTrack = new QPushButton(centralWidget);
        ButtonTrack->setObjectName(QStringLiteral("ButtonTrack"));
        ButtonTrack->setGeometry(QRect(770, 290, 311, 141));
        QFont font;
        font.setPointSize(20);
        ButtonTrack->setFont(font);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 10, 721, 20));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(11);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_3);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(430, 50, 721, 231));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        LabelCamera = new QLabel(layoutWidget1);
        LabelCamera->setObjectName(QStringLiteral("LabelCamera"));
        LabelCamera->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(LabelCamera);

        LabelFeature = new QLabel(layoutWidget1);
        LabelFeature->setObjectName(QStringLiteral("LabelFeature"));
        LabelFeature->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(LabelFeature);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(130, 40, 99, 158));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(100);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ButtonOpenCam = new QPushButton(layoutWidget2);
        ButtonOpenCam->setObjectName(QStringLiteral("ButtonOpenCam"));

        verticalLayout->addWidget(ButtonOpenCam);

        ButtonDisplayPose = new QPushButton(layoutWidget2);
        ButtonDisplayPose->setObjectName(QStringLiteral("ButtonDisplayPose"));

        verticalLayout->addWidget(ButtonDisplayPose);

        ButtonMove = new QPushButton(centralWidget);
        ButtonMove->setObjectName(QStringLiteral("ButtonMove"));
        ButtonMove->setGeometry(QRect(140, 280, 75, 23));
        TextEditDebug = new QPlainTextEdit(centralWidget);
        TextEditDebug->setObjectName(QStringLiteral("TextEditDebug"));
        TextEditDebug->setGeometry(QRect(770, 460, 301, 161));
        uppercomputerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(uppercomputerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1238, 26));
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
        LabelPoseR1->setText(QApplication::translate("uppercomputerClass", "R1:", Q_NULLPTR));
        LabelPoseR2->setText(QApplication::translate("uppercomputerClass", "R2:", Q_NULLPTR));
        LabelPoseR3->setText(QApplication::translate("uppercomputerClass", "R3:", Q_NULLPTR));
        LabelPoseR4->setText(QApplication::translate("uppercomputerClass", "R4:", Q_NULLPTR));
        LabelPoseR5->setText(QApplication::translate("uppercomputerClass", "R5:", Q_NULLPTR));
        LabelPoseR0->setText(QApplication::translate("uppercomputerClass", "R0:", Q_NULLPTR));
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
        ButtonDisplayPose->setText(QApplication::translate("uppercomputerClass", "DisplayPose", Q_NULLPTR));
        ButtonMove->setText(QApplication::translate("uppercomputerClass", "Move", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class uppercomputerClass: public Ui_uppercomputerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPPERCOMPUTER_H
