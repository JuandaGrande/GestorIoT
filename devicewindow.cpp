#include "devicewindow.h"
#include "ui_devicewindow.h"
#include "databasemanager.h"

#include <QInputDialog>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QHeaderView>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

/**
 * @brief Construye la ventana de gestión de dispositivos para un usuario.
 *
 * Configura la tabla de dispositivos, conecta las señales de la interfaz y
 * arranca el temporizador que simula el ping periódico a los dispositivos.
 *
 * @param db Puntero al gestor de base de datos compartido.
 * @param userId Identificador del usuario autenticado.
 * @param parent Widget padre de la ventana (opcional).
 */
DeviceWindow::DeviceWindow(DatabaseManager *db, int userId, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DeviceWindow)
    , m_db(db)
    , m_userId(userId)
{
    ui->setupUi(this);

    ui->tableDevices->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableDevices->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableDevices->horizontalHeader()->setStretchLastSection(true);

    // El usuario puede cambiar el intervalo de simulación mediante el spinBox.
    connect(ui->spinBoxInterval, &QSpinBox::valueChanged,
            this, &DeviceWindow::onIntervalChanged);

    // El temporizador dispara periódicamente la actualización del estado.
    connect(&m_pingTimer, &QTimer::timeout,
            this, &DeviceWindow::onPingTimerTimeout);

    // Arrancar el timer con el valor inicial del spinBox (segundos).
    onIntervalChanged(ui->spinBoxInterval->value());

    // Cargar la lista inicial de dispositivos del usuario.
    on_pushButtonRefresh_clicked();
}

/**
 * @brief Destructor por defecto.
 */
DeviceWindow::~DeviceWindow()
{
    delete ui;
}

/**
 * @brief Crea un nuevo dispositivo a partir de datos introducidos por el usuario.
 *
 * Abre diálogos de texto para capturar nombre, tipo, dirección IP y parámetros
 * de calibración, inserta el dispositivo en la base de datos y recarga la tabla.
 */
void DeviceWindow::on_pushButtonAdd_clicked()
{
    bool ok;

    QString name = QInputDialog::getText(this, "New device",
                                         "Name:", QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    QString type = QInputDialog::getText(this, "New device",
                                         "Type:", QLineEdit::Normal,
                                         "", &ok);
    if (!ok || type.trimmed().isEmpty())
        return;

    QString ip = QInputDialog::getText(this, "New device",
                                       "IP address:", QLineEdit::Normal,
                                       "", &ok);
    if (!ok || ip.trimmed().isEmpty())
        return;

    QString calib = QInputDialog::getText(this, "New device",
                                          "Calibration params:", QLineEdit::Normal,
                                          "", &ok);
    if (!ok)
        return;

    DeviceRecord d;
    d.deviceId = 0; // Lo asigna SQLite automáticamente.
    d.name = name.trimmed();
    d.type = type.trimmed();
    d.ipAddress = ip.trimmed();
    d.calibration = calib.trimmed();
    d.userId = m_userId;

    if (m_db->insertDevice(d)) {
        on_pushButtonRefresh_clicked();
    }
}

/**
 * @brief Edita el dispositivo seleccionado y envía la nueva configuración al ESP32.
 *
 * Permite modificar los campos básicos del dispositivo y guarda los cambios en la
 * base de datos. Si el campo de calibración coincide con alguna palabra clave
 * (WHITE, OFF, RED, GREEN, BLUE, RG, RB, GB), se construye una URL hacia el
 * dispositivo IoT y se envía una petición HTTP GET para aplicar la configuración.
 */
void DeviceWindow::on_pushButtonEdit_clicked()
{
    int row = ui->tableDevices->currentRow();
    if (row < 0)
        return; // Nada seleccionado.

    QString name = ui->tableDevices->item(row, 0)->text();
    QString type = ui->tableDevices->item(row, 1)->text();
    QString ip   = ui->tableDevices->item(row, 2)->text();
    QString cal  = ui->tableDevices->item(row, 3)->text();

    bool ok;

    QString newName = QInputDialog::getText(this, "Edit device",
                                            "Name:", QLineEdit::Normal,
                                            name, &ok);
    if (!ok || newName.trimmed().isEmpty())
        return;

    QString newType = QInputDialog::getText(this, "Edit device",
                                            "Type:", QLineEdit::Normal,
                                            type, &ok);
    if (!ok || newType.trimmed().isEmpty())
        return;

    QString newIp = QInputDialog::getText(this, "Edit device",
                                          "IP address:", QLineEdit::Normal,
                                          ip, &ok);
    if (!ok || newIp.trimmed().isEmpty())
        return;

    QString newCal = QInputDialog::getText(this, "Edit device",
                                           "Calibration params:",
                                           QLineEdit::Normal,
                                           cal, &ok);
    if (!ok)
        return;

    int deviceId = m_db->getDeviceIdByNameIp(name, ip, m_userId);
    if (deviceId < 0)
        return;

    DeviceRecord d;
    d.deviceId    = deviceId;
    d.name        = newName.trimmed();
    d.type        = newType.trimmed();
    d.ipAddress   = newIp.trimmed();
    d.calibration = newCal.trimmed();
    d.userId      = m_userId;

    if (m_db->updateDevice(d)) {
        on_pushButtonRefresh_clicked();

        // Enviar configuración al ESP32 según el valor de calibration.
        QString command = d.calibration.trimmed().toUpper();

        QString path;
        if (command == "WHITE") {
            path = "/white";
        } else if (command == "OFF") {
            path = "/off";
        } else if (command == "RED") {
            path = "/red";
        } else if (command == "GREEN") {
            path = "/green";
        } else if (command == "BLUE") {
            path = "/blue";
        } else if (command == "RG") {
            path = "/rg";
        } else if (command == "RB") {
            path = "/rb";
        } else if (command == "GB") {
            path = "/gb";
        } else {
            return; // No se envía nada para otros valores.
        }

        QString urlString = "http://" + d.ipAddress + path;
        QUrl url(urlString);
        QNetworkRequest request(url);

        // Se crea un QNetworkAccessManager local para disparar la petición HTTP GET.
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);
        nam->get(request);
    }
}

/**
 * @brief Elimina el dispositivo seleccionado de la base de datos.
 *
 * Obtiene la fila seleccionada en la tabla, resuelve su deviceId y lo borra de la
 * tabla devices. Finalmente, recarga la lista mostrada.
 */
void DeviceWindow::on_pushButtonRemove_clicked()
{
    int row = ui->tableDevices->currentRow();
    if (row < 0)
        return; // Nada seleccionado.

    QString name = ui->tableDevices->item(row, 0)->text();
    QString ip   = ui->tableDevices->item(row, 2)->text();

    int deviceId = m_db->getDeviceIdByNameIp(name, ip, m_userId);
    if (deviceId < 0)
        return;

    if (m_db->deleteDevice(deviceId)) {
        on_pushButtonRefresh_clicked();
    }
}

/**
 * @brief Recarga en la tabla todos los dispositivos del usuario actual.
 */
void DeviceWindow::on_pushButtonRefresh_clicked()
{
    QVector<DeviceRecord> devices = m_db->listDevicesForUser(m_userId);

    ui->tableDevices->clearContents();
    ui->tableDevices->setRowCount(devices.size());

    for (int row = 0; row < devices.size(); ++row) {
        const DeviceRecord &d = devices[row];

        ui->tableDevices->setItem(row, 0, new QTableWidgetItem(d.name));
        ui->tableDevices->setItem(row, 1, new QTableWidgetItem(d.type));
        ui->tableDevices->setItem(row, 2, new QTableWidgetItem(d.ipAddress));
        ui->tableDevices->setItem(row, 3, new QTableWidgetItem(d.calibration));
        ui->tableDevices->setItem(row, 4, new QTableWidgetItem("Unknown"));
    }
}

// --- Simulación de ping ---

/**
 * @brief Actualiza el intervalo del temporizador de ping.
 *
 * @param value Nuevo intervalo en segundos introducido en el QSpinBox.
 */
void DeviceWindow::onIntervalChanged(int value)
{
    int intervalMs = value * 1000;
    m_pingTimer.start(intervalMs);
}

/**
 * @brief Slot llamado periódicamente para simular el estado de los dispositivos.
 *
 * Alterna entre "Online" y "Offline" en la columna de estado de la tabla para
 * todos los dispositivos, ilustrando el uso de un temporizador periódico.
 */
void DeviceWindow::onPingTimerTimeout()
{
    static bool toggle = false;  // Va cambiando true/false cada vez.

    int rows = ui->tableDevices->rowCount();
    for (int row = 0; row < rows; ++row) {
        QTableWidgetItem *statusItem = ui->tableDevices->item(row, 4);

        if (!statusItem) {
            statusItem = new QTableWidgetItem;
            ui->tableDevices->setItem(row, 4, statusItem);
        }

        if (toggle) {
            statusItem->setText("Online");
        } else {
            statusItem->setText("Offline");
        }
    }

    toggle = !toggle;
}
