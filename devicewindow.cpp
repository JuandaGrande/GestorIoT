#include "devicewindow.h"
#include "ui_devicewindow.h"
#include "databasemanager.h"

#include <QInputDialog>
#include <QTableWidgetItem>
#include <QAbstractItemView>
#include <QHeaderView>

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

    on_pushButtonRefresh_clicked();
}

DeviceWindow::~DeviceWindow()
{
    delete ui;
}

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
    d.deviceId = 0; // lo pone SQLite
    d.name = name.trimmed();
    d.type = type.trimmed();
    d.ipAddress = ip.trimmed();
    d.calibration = calib.trimmed();
    d.userId = m_userId;

    if (m_db->insertDevice(d)) {
        on_pushButtonRefresh_clicked();
    }
}


void DeviceWindow::on_pushButtonEdit_clicked()
{
    int row = ui->tableDevices->currentRow();
    if (row < 0)
        return; // nada seleccionado

    QString name = ui->tableDevices->item(row, 0)->text();
    QString type = ui->tableDevices->item(row, 1)->text();
    QString ip   = ui->tableDevices->item(row, 2)->text();
    QString cal  = ui->tableDevices->item(row, 3)->text();

    // Pedir nuevos valores (inicializando con los actuales)
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

    // Obtener deviceId en BD
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
    }
}



void DeviceWindow::on_pushButtonRemove_clicked()
{
    int row = ui->tableDevices->currentRow();
    if (row < 0)
        return; // nada seleccionado

    QString name = ui->tableDevices->item(row, 0)->text();
    QString ip   = ui->tableDevices->item(row, 2)->text();

    int deviceId = m_db->getDeviceIdByNameIp(name, ip, m_userId);
    if (deviceId < 0)
        return;

    if (m_db->deleteDevice(deviceId)) {
        on_pushButtonRefresh_clicked();
    }
}



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
        ui->tableDevices->setItem(row, 4, new QTableWidgetItem("Unknown")); // status por ahora
    }
}

