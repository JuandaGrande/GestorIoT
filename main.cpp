#include "mainwindow.h"
#include <QApplication>
#include "databasemanager.h"

/**
 * @brief Punto de entrada principal de la aplicación Gestor_IoT.
 *
 * Crea el objeto QApplication necesario para cualquier aplicación Qt con interfaz
 * gráfica, inicializa el gestor de base de datos y muestra la ventana principal
 * de login y registro.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Vector de argumentos de línea de comandos.
 * @return Código de retorno del bucle de eventos de Qt.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);      ///< Objeto principal de aplicación Qt.

    DatabaseManager db;              ///< Gestor de base de datos compartido.
    MainWindow w(&db);               ///< Ventana principal que utiliza la base de datos.
    w.show();

    return a.exec();
}
