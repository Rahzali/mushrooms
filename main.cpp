#include <QGuiApplication>
#include <QQuickWindow>
#include <QQmlEngine>
#include "MapView/MapView.h"

int qInitResources_qml();

int main(int argc, char *argv[])
{
    qInitResources_qml(); // ensures resource is registered

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
