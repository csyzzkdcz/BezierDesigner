/********************************************************************************
** Form generated from reading UI file 'bezier.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEZIER_H
#define UI_BEZIER_H

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

class Ui_BezierClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BezierClass)
    {
        if (BezierClass->objectName().isEmpty())
            BezierClass->setObjectName(QStringLiteral("BezierClass"));
        BezierClass->resize(600, 400);
        menuBar = new QMenuBar(BezierClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BezierClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BezierClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BezierClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BezierClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BezierClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BezierClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BezierClass->setStatusBar(statusBar);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
