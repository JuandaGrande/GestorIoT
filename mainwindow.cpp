#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "databasemanager.h"
#include "devicewindow.h"

/**
 * @brief Construye la ventana principal de login y registro.
 *
 * Inicializa la interfaz gráfica generada por Qt Designer y guarda el puntero
 * al gestor de base de datos que se utilizará para las operaciones de usuario.
 */
MainWindow::MainWindow(DatabaseManager *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_db(db)
{
    ui->setupUi(this);
}

/**
 * @brief Destructor por defecto.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Maneja el evento de clic sobre el botón de login.
 *
 * Lee el nombre de usuario y la contraseña introducidos, valida que no estén vacíos
 * y consulta la base de datos para comprobar las credenciales. Si el login es correcto,
 * obtiene el identificador de usuario y crea (si es necesario) la ventana de
 * dispositivos asociada a ese usuario, ocultando la ventana de login.
 */
void MainWindow::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->labelStatus->setStyleSheet("color: red;");
        ui->labelStatus->setText("Por favor ingresa usuario y contraseña.");
        return;
    }

    // Verificar usuario/contraseña en la base de datos.
    if (!m_db->checkUserPassword(username, password)) {
        ui->labelStatus->setStyleSheet("color: red;");
        ui->labelStatus->setText("Usuario o contraseña incorrectos.");
        return;
    }

    // Login correcto.
    ui->labelStatus->setStyleSheet("color: green;");
    ui->labelStatus->setText("Login correcto. Bienvenido " + username + ".");

    // Obtener el userId real de este usuario.
    int userId = m_db->getUserId(username);
    if (userId < 0) {
        ui->labelStatus->setStyleSheet("color: red;");
        ui->labelStatus->setText("Error obteniendo el ID del usuario.");
        return;
    }

    // Crear la ventana de dispositivos si aún no existe.
    if (!m_deviceWindow) {
        m_deviceWindow = new DeviceWindow(m_db, userId, this);
    }

    m_deviceWindow->show();
    this->hide();
}

/**
 * @brief Maneja el evento de clic sobre el botón de registro.
 *
 * Crea un nuevo usuario en la base de datos con los datos introducidos en los
 * campos de texto. Muestra un mensaje de estado indicando si el registro fue
 * exitoso o si el nombre de usuario ya existe u ocurrió algún error.
 */
void MainWindow::on_pushButtonRegister_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->labelStatus->setStyleSheet("color: red;");
        ui->labelStatus->setText("Usuario y contraseña no pueden estar vacíos.");
        return;
    }

    if (m_db->insertUser(username, password)) {
        ui->labelStatus->setStyleSheet("color: green;");
        ui->labelStatus->setText("Usuario registrado correctamente.");
    } else {
        ui->labelStatus->setStyleSheet("color: red;");
        ui->labelStatus->setText("No se pudo registrar (¿usuario ya existe?).");
    }
}
