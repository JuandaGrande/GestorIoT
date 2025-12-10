#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DatabaseManager;
class DeviceWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Ventana inicial de la aplicación que gestiona el login y registro de usuarios.
 *
 * Esta ventana permite crear nuevos usuarios y autenticarse contra la base de datos.
 * Tras un inicio de sesión correcto, crea y muestra la ventana de gestión de dispositivos
 * asociada al usuario autenticado.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construye la ventana principal de autenticación.
     *
     * @param db Puntero al gestor de base de datos compartido por toda la aplicación.
     * @param parent Widget padre de la ventana (opcional).
     */
    explicit MainWindow(DatabaseManager *db, QWidget *parent = nullptr);

    /**
     * @brief Destructor por defecto.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot asociado al botón de login.
     *
     * Valida el par usuario/contraseña frente a la base de datos. Si las credenciales
     * son correctas, obtiene el identificador del usuario y abre la ventana de
     * dispositivos para dicho usuario.
     */
    void on_pushButtonLogin_clicked();

    /**
     * @brief Slot asociado al botón de registro.
     *
     * Crea un nuevo usuario en la base de datos con el nombre y contraseña
     * introducidos en la interfaz, mostrando mensajes de estado según el resultado.
     */
    void on_pushButtonRegister_clicked();

private:
    Ui::MainWindow *ui;           ///< Interfaz generada por Qt Designer para la ventana de login.
    DatabaseManager *m_db;        ///< Puntero al gestor de base de datos utilizado para operaciones de usuario.
    DeviceWindow *m_deviceWindow; ///< Ventana de gestión de dispositivos asociada al usuario autenticado.
    int m_currentUserId;          ///< Identificador del usuario actualmente autenticado (-1 si no hay sesión activa).
};

#endif // MAINWINDOW_H
