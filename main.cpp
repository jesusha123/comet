#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "FileSystemModel.h"
#include "NetworkManager.h"
#include "RequestLoader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");
    QQmlApplicationEngine engine;

    NetworkManager networkManager;
    engine.rootContext()->setContextProperty("NetworkManager", &networkManager);
    FileSystemModel fileSystemModel;
    engine.rootContext()->setContextProperty("FileSystemModel", &fileSystemModel);
    RequestLoader requestLoader;
    engine.rootContext()->setContextProperty("RequestLoader", &requestLoader);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("comet", "Main");

    return app.exec();
}
