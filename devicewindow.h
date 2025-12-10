#include <QMainWindow>
#include <QTimer>

class DatabaseManager;

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceWindow; }
QT_END_NAMESPACE

class DeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceWindow(DatabaseManager *db, int userId, QWidget *parent = nullptr);
    ~DeviceWindow();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonRefresh_clicked();

    void onIntervalChanged(int value);
    void onPingTimerTimeout();

private:
    Ui::DeviceWindow *ui;
    DatabaseManager *m_db;
    int m_userId;
    QTimer m_pingTimer;
};
