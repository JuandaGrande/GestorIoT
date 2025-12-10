#include "databasemanager.h"

#include <QStandardPaths>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief Constructor por defecto.
 *
 * Llama a initDatabase() para abrir la base de datos y crear las tablas si es necesario.
 */
DatabaseManager::DatabaseManager()
{
    initDatabase();
}

/**
 * @brief Inicializa la base de datos SQLite en una ruta de datos de la aplicación.
 *
 * Crea el directorio de datos de la aplicación si no existe, abre (o crea) el archivo
 * iot_config.db y delega en createTables() la creación de las tablas.
 *
 * @return true si la base de datos se abrió correctamente y las tablas están listas,
 *         false si se produce algún error al crear el directorio, abrir la BD o crear tablas.
 */
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

/**
 * @brief Crea las tablas users y devices si aún no existen.
 *
 * @return true si ambas tablas se crean correctamente o ya existen, false en caso de error.
 */
bool DatabaseManager::createTables()
{
    QSqlQuery query;

    // Tabla de usuarios
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "userId INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username TEXT NOT NULL UNIQUE,"
            "password TEXT NOT NULL)"
            )) {
        return false;
    }

    // Tabla de dispositivos asociados a cada usuario
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

/**
 * @brief Inserta un nuevo usuario en la tabla users.
 */
bool DatabaseManager::insertUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:u, :p)");
    query.bindValue(":u", username);
    query.bindValue(":p", password); // TODO: reemplazar por hash de la contraseña
    return query.exec();
}

/**
 * @brief Comprueba si existe un usuario con el par usuario/contraseña indicado.
 */
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

/**
 * @brief Inserta un nuevo dispositivo en la tabla devices.
 */
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

/**
 * @brief Devuelve el identificador interno de un usuario a partir de su nombre.
 */
int DatabaseManager::getUserId(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT userId FROM users WHERE username = :u");
    query.bindValue(":u", username);
    if (!query.exec())
        return -1;

    if (query.next())
        return query.value(0).toInt();

    return -1;
}

/**
 * @brief Devuelve todos los dispositivos pertenecientes a un usuario.
 */
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

/**
 * @brief Actualiza los datos de un dispositivo existente en la tabla devices.
 */
bool DatabaseManager::updateDevice(const DeviceRecord &device)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE devices SET name = :name, type = :type, "
        "ipAddress = :ip, calibration = :cal "
        "WHERE deviceId = :id");
    query.bindValue(":name", device.name);
    query.bindValue(":type", device.type);
    query.bindValue(":ip", device.ipAddress);
    query.bindValue(":cal", device.calibration);
    query.bindValue(":id", device.deviceId);
    return query.exec();
}

/**
 * @brief Elimina un dispositivo por su identificador.
 */
bool DatabaseManager::deleteDevice(int deviceId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM devices WHERE deviceId = :id");
    query.bindValue(":id", deviceId);
    return query.exec();
}

/**
 * @brief Obtiene el deviceId de un dispositivo a partir de nombre, IP y usuario.
 */
int DatabaseManager::getDeviceIdByNameIp(const QString &name,
                                         const QString &ipAddress,
                                         int userId)
{
    QSqlQuery query;
    query.prepare(
        "SELECT deviceId FROM devices "
        "WHERE name = :name AND ipAddress = :ip AND userId = :uid");
    query.bindValue(":name", name);
    query.bindValue(":ip", ipAddress);
    query.bindValue(":uid", userId);
    if (!query.exec())
        return -1;
    if (query.next())
        return query.value(0).toInt();
    return -1;
}
