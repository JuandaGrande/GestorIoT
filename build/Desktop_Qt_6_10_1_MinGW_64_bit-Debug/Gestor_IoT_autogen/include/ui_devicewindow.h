/********************************************************************************
** Form generated from reading UI file 'devicewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEWINDOW_H
#define UI_DEVICEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DeviceWindow)
    {
        if (DeviceWindow->objectName().isEmpty())
            DeviceWindow->setObjectName("DeviceWindow");
        DeviceWindow->resize(800, 600);
        centralwidget = new QWidget(DeviceWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 20, 291, 71));
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        DeviceWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DeviceWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        DeviceWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DeviceWindow);
        statusbar->setObjectName("statusbar");
        DeviceWindow->setStatusBar(statusbar);

        retranslateUi(DeviceWindow);

        QMetaObject::connectSlotsByName(DeviceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DeviceWindow)
    {
        DeviceWindow->setWindowTitle(QCoreApplication::translate("DeviceWindow", "IoT Device Manager", nullptr));
        label->setText(QCoreApplication::translate("DeviceWindow", "Dispositivos IoT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceWindow: public Ui_DeviceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEWINDOW_H
