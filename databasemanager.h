#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QVector>

struct DeviceRecord {
    int deviceId;
    QString name;
    QString type;
    QString ipAddress;
    QString calibration;
    int userId;
};

class DatabaseManager
{
public:
    DatabaseManager();
    bool initDatabase();

    // Usuarios (por ahora solo login/register)
    bool insertUser(const QString &username, const QString &password);
    bool checkUserPassword(const QString &username, const QString &password);
    // Dispositivos
    bool insertDevice(const DeviceRecord &device);
    QVector<DeviceRecord> listDevicesForUser(int userId);


private:
    bool createTables();
};

#endif // DATABASEMANAGER_H
