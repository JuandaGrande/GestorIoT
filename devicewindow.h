#ifndef DEVICEWINDOW_H
#define DEVICEWINDOW_H

#include <QMainWindow>

class DatabaseManager;

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceWindow; }
QT_END_NAMESPACE

class DeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceWindow(DatabaseManager *db, QWidget *parent = nullptr);
    ~DeviceWindow();

private:
    Ui::DeviceWindow *ui;
    DatabaseManager *m_db;
};

#endif // DEVICEWINDOW_H
