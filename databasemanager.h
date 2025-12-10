#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QVector>

/**
 * @brief Estructura que representa un dispositivo IoT almacenado en la base de datos.
 */
struct DeviceRecord {
    int deviceId;        ///< Identificador único del dispositivo (PRIMARY KEY en la tabla devices).
    QString name;        ///< Nombre descriptivo del dispositivo.
    QString type;        ///< Tipo de dispositivo (por ejemplo: LED, SENSOR, RELAY).
    QString ipAddress;   ///< Dirección IP del dispositivo IoT en la red.
    QString calibration; ///< Parámetros de calibración o configuración (por ejemplo ON/OFF).
    int userId;          ///< Identificador del usuario propietario del dispositivo (FOREIGN KEY a users.userId).
};

/**
 * @brief Clase responsable de inicializar y gestionar el acceso a la base de datos SQLite.
 *
 * Encapsula la creación de la base de datos, las tablas y las operaciones
 * básicas de inserción, consulta, actualización y borrado de usuarios y dispositivos.
 */
class DatabaseManager
{
public:
    /**
     * @brief Construye el gestor de base de datos e inicializa la conexión SQLite.
     *
     * El constructor llama internamente a initDatabase() para abrir el archivo
     * de base de datos y crear las tablas necesarias si aún no existen.
     */
    DatabaseManager();

    /**
     * @brief Inicializa la base de datos SQLite.
     * @return true si la base de datos se abrió correctamente y las tablas fueron creadas, false en caso contrario.
     */
    bool initDatabase();

    // Usuarios

    /**
     * @brief Inserta un nuevo usuario en la tabla users.
     * @param username Nombre de usuario.
     * @param password Contraseña asociada al usuario (actualmente en texto plano).
     * @return true si la inserción se realizó correctamente, false si ocurrió un error
     *         (por ejemplo, nombre de usuario duplicado).
     */
    bool insertUser(const QString &username, const QString &password);

    /**
     * @brief Verifica si existe un usuario con el par usuario/contraseña indicado.
     * @param username Nombre de usuario.
     * @param password Contraseña del usuario.
     * @return true si el usuario existe y la contraseña coincide, false en caso contrario.
     */
    bool checkUserPassword(const QString &username, const QString &password);

    /**
     * @brief Obtiene el identificador interno (userId) de un usuario.
     * @param username Nombre de usuario cuyo ID se desea obtener.
     * @return El userId correspondiente si se encuentra el usuario, o -1 si no existe
     *         o si ocurre algún error en la consulta.
     */
    int getUserId(const QString &username);

    // Dispositivos

    /**
     * @brief Inserta un nuevo dispositivo en la tabla devices.
     * @param device Estructura con los datos del dispositivo a insertar.
     * @return true si la inserción fue exitosa, false en caso de error.
     */
    bool insertDevice(const DeviceRecord &device);

    /**
     * @brief Recupera todos los dispositivos asociados a un usuario.
     * @param userId Identificador del usuario propietario de los dispositivos.
     * @return Vector con los registros de dispositivos encontrados (puede estar vacío).
     */
    QVector<DeviceRecord> listDevicesForUser(int userId);

    /**
     * @brief Actualiza los datos de un dispositivo existente.
     * @param device Estructura que contiene el deviceId y los nuevos valores a almacenar.
     * @return true si la actualización fue exitosa, false si ocurrió algún error.
     */
    bool updateDevice(const DeviceRecord &device);

    /**
     * @brief Elimina un dispositivo de la base de datos.
     * @param deviceId Identificador del dispositivo que se desea borrar.
     * @return true si el dispositivo se eliminó correctamente, false en caso contrario.
     */
    bool deleteDevice(int deviceId);

    /**
     * @brief Obtiene el deviceId de un dispositivo a partir de su nombre, IP y usuario.
     *
     * Se utiliza como ayuda cuando la interfaz gráfica solo conoce el nombre, la IP
     * y el userId del dispositivo seleccionado.
     *
     * @param name Nombre del dispositivo.
     * @param ipAddress Dirección IP del dispositivo.
     * @param userId Identificador del usuario propietario.
     * @return El deviceId correspondiente si se encuentra un dispositivo que cumpla
     *         las condiciones, o -1 si no existe o si ocurre un error.
     */
    int getDeviceIdByNameIp(const QString &name,
                            const QString &ipAddress,
                            int userId);

private:
    /**
     * @brief Crea las tablas necesarias en la base de datos si aún no existen.
     * @return true si todas las tablas fueron creadas o ya existían, false si se produjo algún error.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H
