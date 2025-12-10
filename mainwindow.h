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
 * Tras un inicio de sesión correcto, crea y muestra la ventana de gestión de
 * dispositivos asociada al usuario autenticado.
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
     */
    void on_pushButtonLogin_clicked();

    /**
     * @brief Slot asociado al botón de registro.
     */
    void on_pushButtonRegister_clicked();

private:
    Ui::MainWindow *ui;                  ///< Interfaz generada por Qt Designer.
    DatabaseManager *m_db;               ///< Gestor de base de datos.
    DeviceWindow *m_deviceWindow = nullptr; ///< Ventana de dispositivos (se crea al hacer login).
    int m_currentUserId = -1;            ///< ID del usuario autenticado.
};

#endif // MAINWINDOW_H
