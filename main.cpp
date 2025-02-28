#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "NetworkManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    NetworkManager networkManager;
    engine.rootContext()->setContextProperty("NetworkManager", &networkManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("comet", "Main");

    return app.exec();
}
