#include "RequestStorage.h"
#include <QApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

RequestStorage::RequestStorage()
{
    appDataDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if(appDataDirectory.isEmpty() || !QDir().mkpath(appDataDirectory)) {
        qCritical("Cannot write to application data directory");
        qApp->exit(1);
    }
}

bool RequestStorage::saveRequest(const Request& request, QString name)
{
    qInfo("Saving request started");
    QFile saveFile(appDataDirectory + "/" + name + ".json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    qInfo("File opened successfully");

    QJsonObject root;
    root["url"] = request.url.toString();
    root["method"] = request.method;
    root["body"] = QString(request.body);

    root["headers"] = getJsonHeaders(request);

    saveFile.write(QJsonDocument(root).toJson());

    qInfo("Saving request finished");

    return true;
}

QJsonArray RequestStorage::getJsonHeaders(const Request& request)
{
    QJsonArray arr;

    for(const auto &header : request.headers) {
        QJsonObject obj;
        obj["key"] = QString(header.first);
        obj["value"] = QString(header.second);
        arr.append(obj);
    }

    return arr;
}

QList<Request> RequestStorage::readCollection()
{
    QList<Request> list;

    qInfo("Reading collection started");
    QDir directory(appDataDirectory);
    QStringList requestFileNames = directory.entryList(QStringList() << "*.json", QDir::Files);

    foreach(QString requestFileName, requestFileNames) {
        qInfo("Loading request: %s", qPrintable(requestFileName));

        QFile readFile(appDataDirectory + "/" + requestFileName);

        if (readFile.open(QIODevice::ReadOnly)) {
            QByteArray data = readFile.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(data));

            Request request;

            auto root = jsonDoc.object();
            request.name = QFileInfo(requestFileName).baseName();
            request.url.setUrl(root["url"].toString());
            request.method = root["method"].toString();
            request.body = root["body"].toString().toUtf8();
            auto headerArray = root["headers"].toArray();

            for(auto header : headerArray) {
                auto key = header.toObject()["key"].toString().toUtf8();
                auto value = header.toObject()["value"].toString().toUtf8();
                request.headers.append(qMakePair(key, value));
            }

            list.append(request);
        } else {
            qWarning("Couldn't open read file: %s", qPrintable(requestFileName));
        }
    }

    return list;
}
