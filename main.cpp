#include "mainwindow.h"
#include <QApplication>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);      // 1) primero la app Qt

    DatabaseManager db;              // 2) luego la BD
    MainWindow w(&db);               // 3) pasar puntero a la ventana
    w.show();

    return a.exec();
}
