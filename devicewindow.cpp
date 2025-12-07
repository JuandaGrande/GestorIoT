#include "devicewindow.h"
#include "ui_devicewindow.h"
#include "databasemanager.h"

DeviceWindow::DeviceWindow(DatabaseManager *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DeviceWindow)
    , m_db(db)
{
    ui->setupUi(this);
}

DeviceWindow::~DeviceWindow()
{
    delete ui;
}
