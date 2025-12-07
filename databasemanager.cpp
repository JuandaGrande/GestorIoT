#include "databasemanager.h"

#include <QStandardPaths>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

DatabaseManager::DatabaseManager()
{
    initDatabase();
}

bool DatabaseManager::initDatabase()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    if (!dir.mkpath(dataDir)) {
        return false;
    }

    QString dbPath = dataDir + "/iot_config.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        return false;
    }

    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "userId INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username TEXT NOT NULL UNIQUE,"
            "password TEXT NOT NULL)"
            )) {
        return false;
    }
    // Tabla devices
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS devices ("
            "deviceId INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "type TEXT NOT NULL,"
            "ipAddress TEXT NOT NULL,"
            "calibration TEXT,"
            "userId INTEGER NOT NULL,"
            "FOREIGN KEY(userId) REFERENCES users(userId))"
            )) {
        return false;
    }


    return true;
}

bool DatabaseManager::insertUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:u, :p)");
    query.bindValue(":u", username);
    query.bindValue(":p", password); // luego lo cambiaremos a hash
    return query.exec();
}

bool DatabaseManager::checkUserPassword(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :u AND password = :p");
    query.bindValue(":u", username);
    query.bindValue(":p", password);
    if (!query.exec()) {
        return false;
    }
    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}


bool DatabaseManager::insertDevice(const DeviceRecord &device)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO devices (name, type, ipAddress, calibration, userId) "
        "VALUES (:name, :type, :ip, :cal, :uid)");
    query.bindValue(":name", device.name);
    query.bindValue(":type", device.type);
    query.bindValue(":ip", device.ipAddress);
    query.bindValue(":cal", device.calibration);
    query.bindValue(":uid", device.userId);
    return query.exec();
}

QVector<DeviceRecord> DatabaseManager::listDevicesForUser(int userId)
{
    QVector<DeviceRecord> devices;

    QSqlQuery query;
    query.prepare(
        "SELECT deviceId, name, type, ipAddress, calibration, userId "
        "FROM devices WHERE userId = :uid");
    query.bindValue(":uid", userId);

    if (!query.exec()) {
        return devices;
    }

    while (query.next()) {
        DeviceRecord d;
        d.deviceId    = query.value(0).toInt();
        d.name        = query.value(1).toString();
        d.type        = query.value(2).toString();
        d.ipAddress   = query.value(3).toString();
        d.calibration = query.value(4).toString();
        d.userId      = query.value(5).toInt();
        devices.append(d);
    }

    return devices;
}
