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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uppercomputerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *uppercomputerClass)
    {
        if (uppercomputerClass->objectName().isEmpty())
            uppercomputerClass->setObjectName(QStringLiteral("uppercomputerClass"));
        uppercomputerClass->resize(600, 400);
        menuBar = new QMenuBar(uppercomputerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        uppercomputerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(uppercomputerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        uppercomputerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(uppercomputerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        uppercomputerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(uppercomputerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        uppercomputerClass->setStatusBar(statusBar);

        retranslateUi(uppercomputerClass);

        QMetaObject::connectSlotsByName(uppercomputerClass);
    } // setupUi

    void retranslateUi(QMainWindow *uppercomputerClass)
    {
        uppercomputerClass->setWindowTitle(QApplication::translate("uppercomputerClass", "uppercomputer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class uppercomputerClass: public Ui_uppercomputerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPPERCOMPUTER_H
