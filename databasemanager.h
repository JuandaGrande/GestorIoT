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

    // Usuarios
    bool insertUser(const QString &username, const QString &password);
    bool checkUserPassword(const QString &username, const QString &password);
    int  getUserId(const QString &username);
    // Dispositivos
    bool insertDevice(const DeviceRecord &device);
    QVector<DeviceRecord> listDevicesForUser(int userId);
    bool updateDevice(const DeviceRecord &device);
    bool deleteDevice(int deviceId);
    int  getDeviceIdByNameIp(const QString &name,
                            const QString &ipAddress,
                            int userId);



private:
    bool createTables();
};

#endif // DATABASEMANAGER_H
