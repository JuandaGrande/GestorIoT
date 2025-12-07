#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DatabaseManager;
class DeviceWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DatabaseManager *db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager *m_db;
    DeviceWindow *m_deviceWindow = nullptr;
    int m_currentUserId = -1;
};

#endif // MAINWINDOW_H
