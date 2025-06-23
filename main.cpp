#include <QGuiApplication>
#include <QQuickWindow>
#include <QQmlEngine>
#include "MapView/MapView.h"
#include <iostream>
#include <mysqlx/xdevapi.h>

int qInitResources_qml();

int main(int argc, char *argv[])
{
    qInitResources_qml(); // ensures resource is registered

    try {
        mysqlx::Session sess("localhost", 33060, "root", "Zaq12wsx");

        mysqlx::Schema db = sess.getSchema("grzyby");
        mysqlx::Table table = db.getTable("grzyb");
        mysqlx::RowResult res = table.select("*").execute();

        for (mysqlx::Row row : res) {
            for (unsigned int i = 0; i < row.colCount(); ++i) {
                std::cout << row[i] << " ";
            }
            std::cout << std::endl;
        }
    } catch (...) {
        std::cerr << "error" << std::endl;
    }

    QGuiApplication app(argc, argv);

    // Create QQuickWindow manually
    QQuickWindow window;
    window.setWidth(800);
    window.setHeight(600);
    window.setTitle("Manual QQuickWindow");

    // Create QQmlEngine
    QQmlEngine engine;

    // Create MapView, give it the window and engine
    MapView mapView(&window, &engine, &app);

    // Show the window
    window.show();

    return app.exec();
}
