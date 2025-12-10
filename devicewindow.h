#include <QMainWindow>
#include <QTimer>

class DatabaseManager;

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceWindow; }
QT_END_NAMESPACE

/**
 * @brief Ventana principal para la gestión de dispositivos IoT.
 *
 * Muestra en una tabla todos los dispositivos asociados al usuario autenticado,
 * permite crear, editar y eliminar dispositivos almacenados en la base de datos
 * y simula el estado de conexión de cada uno mediante un temporizador.
 */
class DeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construye la ventana de dispositivos.
     *
     * @param db Puntero al gestor de base de datos compartido por la aplicación.
     * @param userId Identificador del usuario autenticado cuyos dispositivos se mostrarán.
     * @param parent Widget padre de la ventana (opcional).
     */
    explicit DeviceWindow(DatabaseManager *db, int userId, QWidget *parent = nullptr);

    /**
     * @brief Destructor por defecto.
     */
    ~DeviceWindow();

private slots:
    /**
     * @brief Slot asociado al botón "Add".
     *
     * Abre diálogos de entrada para capturar los datos de un nuevo dispositivo y lo
     * inserta en la base de datos, actualizando la tabla de la interfaz.
     */
    void on_pushButtonAdd_clicked();

    /**
     * @brief Slot asociado al botón "Edit".
     *
     * Permite modificar los datos del dispositivo seleccionado en la tabla, guarda
     * los cambios en la base de datos y, en la versión extendida, envía la nueva
     * configuración al dispositivo IoT.
     */
    void on_pushButtonEdit_clicked();

    /**
     * @brief Slot asociado al botón "Remove".
     *
     * Elimina de la base de datos el dispositivo seleccionado en la tabla y refresca
     * el contenido mostrado al usuario.
     */
    void on_pushButtonRemove_clicked();

    /**
     * @brief Slot asociado al botón "Refresh".
     *
     * Recarga desde la base de datos todos los dispositivos del usuario actual y
     * repuebla la tabla de la ventana.
     */
    void on_pushButtonRefresh_clicked();

    /**
     * @brief Slot llamado cuando cambia el valor del intervalo de actualización.
     *
     * Ajusta el periodo del temporizador de ping a partir del valor indicado
     * (expresado en segundos en el control QSpinBox).
     *
     * @param value Nuevo intervalo en segundos.
     */
    void onIntervalChanged(int value);

    /**
     * @brief Slot disparado periódicamente por el temporizador de ping.
     *
     * Recorre la tabla de dispositivos y actualiza la columna de estado (Status)
     * simulando un ping o una comprobación de conectividad para cada dispositivo.
     */
    void onPingTimerTimeout();

private:
    Ui::DeviceWindow *ui;   ///< Interfaz generada por Qt Designer.
    DatabaseManager *m_db;  ///< Puntero al gestor de base de datos compartido.
    int m_userId;           ///< Identificador del usuario cuyos dispositivos se gestionan.
    QTimer m_pingTimer;     ///< Temporizador usado para la simulación periódica del estado de los dispositivos.
};
