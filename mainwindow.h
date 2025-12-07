#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DatabaseManager;
class DeviceWindow;   // si ya creaste la ventana de dispositivos

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
    DatabaseManager *m_db;          // único puntero a la BD
    DeviceWindow *m_deviceWindow = nullptr;  // opcional, para la segunda ventana
};

#endif // MAINWINDOW_H
