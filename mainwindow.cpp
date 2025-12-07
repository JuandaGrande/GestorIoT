#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "databasemanager.h"
#include "devicewindow.h"

MainWindow::MainWindow(DatabaseManager *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_db(db)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
    {
        QString username = ui->lineEditUsername->text().trimmed();
        QString password = ui->lineEditPassword->text().trimmed();

        if (username.isEmpty() || password.isEmpty()) {
            ui->labelStatus->setStyleSheet("color: red;");
            ui->labelStatus->setText("Por favor ingresa usuario y contraseña.");
            return;
        }

        // Verificar usuario/contraseña en la base de datos
        if (!m_db->checkUserPassword(username, password)) {
            ui->labelStatus->setStyleSheet("color: red;");
            ui->labelStatus->setText("Usuario o contraseña incorrectos.");
            return;
        }

        // Login correcto
        ui->labelStatus->setStyleSheet("color: green;");
        ui->labelStatus->setText("Login correcto. Bienvenido " + username + ".");

        // Obtener el userId real de este usuario
        int userId = m_db->getUserId(username);
        if (userId < 0) {
            ui->labelStatus->setStyleSheet("color: red;");
            ui->labelStatus->setText("Error obteniendo el ID del usuario.");
            return;
        }

        // Crear la ventana de dispositivos si aún no existe
        if (!m_deviceWindow) {
            m_deviceWindow = new DeviceWindow(m_db, userId, this);
        }

        m_deviceWindow->show();
        this->hide();
    }




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
