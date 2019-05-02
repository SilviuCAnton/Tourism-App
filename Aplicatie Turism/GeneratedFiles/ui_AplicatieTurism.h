/********************************************************************************
** Form generated from reading UI file 'AplicatieTurism.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APLICATIETURISM_H
#define UI_APLICATIETURISM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AplicatieTurismClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AplicatieTurismClass)
    {
        if (AplicatieTurismClass->objectName().isEmpty())
            AplicatieTurismClass->setObjectName(QString::fromUtf8("AplicatieTurismClass"));
        AplicatieTurismClass->resize(600, 400);
        menuBar = new QMenuBar(AplicatieTurismClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AplicatieTurismClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AplicatieTurismClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AplicatieTurismClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AplicatieTurismClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AplicatieTurismClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AplicatieTurismClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AplicatieTurismClass->setStatusBar(statusBar);

        retranslateUi(AplicatieTurismClass);

        QMetaObject::connectSlotsByName(AplicatieTurismClass);
    } // setupUi

    void retranslateUi(QMainWindow *AplicatieTurismClass)
    {
        AplicatieTurismClass->setWindowTitle(QApplication::translate("AplicatieTurismClass", "AplicatieTurism", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AplicatieTurismClass: public Ui_AplicatieTurismClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APLICATIETURISM_H
