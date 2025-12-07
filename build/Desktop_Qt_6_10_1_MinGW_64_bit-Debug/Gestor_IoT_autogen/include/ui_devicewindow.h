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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelTitle;
    QTableWidget *tableDevices;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonRemove;
    QPushButton *pushButtonRefresh;
    QLabel *labelIntervalText;
    QSpinBox *spinBoxInterval;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DeviceWindow)
    {
        if (DeviceWindow->objectName().isEmpty())
            DeviceWindow->setObjectName("DeviceWindow");
        DeviceWindow->resize(800, 600);
        centralwidget = new QWidget(DeviceWindow);
        centralwidget->setObjectName("centralwidget");
        labelTitle = new QLabel(centralwidget);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(190, 20, 431, 71));
        QFont font;
        font.setPointSize(28);
        labelTitle->setFont(font);
        tableDevices = new QTableWidget(centralwidget);
        if (tableDevices->columnCount() < 5)
            tableDevices->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableDevices->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableDevices->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableDevices->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableDevices->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableDevices->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableDevices->setObjectName("tableDevices");
        tableDevices->setGeometry(QRect(40, 110, 721, 192));
        tableDevices->setColumnCount(5);
        pushButtonAdd = new QPushButton(centralwidget);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setGeometry(QRect(150, 360, 80, 24));
        pushButtonEdit = new QPushButton(centralwidget);
        pushButtonEdit->setObjectName("pushButtonEdit");
        pushButtonEdit->setGeometry(QRect(290, 360, 80, 24));
        pushButtonRemove = new QPushButton(centralwidget);
        pushButtonRemove->setObjectName("pushButtonRemove");
        pushButtonRemove->setGeometry(QRect(440, 360, 80, 24));
        pushButtonRefresh = new QPushButton(centralwidget);
        pushButtonRefresh->setObjectName("pushButtonRefresh");
        pushButtonRefresh->setGeometry(QRect(580, 360, 80, 24));
        labelIntervalText = new QLabel(centralwidget);
        labelIntervalText->setObjectName("labelIntervalText");
        labelIntervalText->setGeometry(QRect(490, 310, 101, 20));
        spinBoxInterval = new QSpinBox(centralwidget);
        spinBoxInterval->setObjectName("spinBoxInterval");
        spinBoxInterval->setGeometry(QRect(591, 310, 61, 25));
        spinBoxInterval->setMinimum(1);
        spinBoxInterval->setMaximum(3600);
        spinBoxInterval->setValue(5);
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
        labelTitle->setText(QCoreApplication::translate("DeviceWindow", "Gestor de Dispositivos IoT", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableDevices->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DeviceWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableDevices->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DeviceWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableDevices->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DeviceWindow", "IP Adress", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableDevices->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DeviceWindow", "Calibration", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableDevices->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DeviceWindow", "Status", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("DeviceWindow", "Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("DeviceWindow", "Edit", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("DeviceWindow", "Remove", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("DeviceWindow", "Refresh", nullptr));
        labelIntervalText->setText(QCoreApplication::translate("DeviceWindow", "Update Interval (s): ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceWindow: public Ui_DeviceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEWINDOW_H
