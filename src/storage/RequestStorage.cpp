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

bool RequestStorage::save(const Request& request)
{
    qInfo("Saving request started");
    QFile saveFile(appDataDirectory + "/save.json");

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

Request* RequestStorage::read()
{
    Request* request = nullptr;

    qInfo("Reading request started");
    QFile readFile(appDataDirectory + "/save.json");

    if (readFile.open(QIODevice::ReadOnly)) {
        qInfo("File opened successfully");

        QByteArray data = readFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(data));

        request = new Request();

        auto root = jsonDoc.object();
        request->url.setUrl(root["url"].toString());
        request->method = root["method"].toString();
        request->body = root["body"].toString().toUtf8();
        auto headerArray = root["headers"].toArray();
        for(auto header : headerArray) {
            auto key = header.toObject()["key"].toString().toUtf8();
            auto value = header.toObject()["value"].toString().toUtf8();
            request->headers.append(qMakePair(key, value));
        }
    } else {
        qWarning("Couldn't open read file.");
    }

    return request;
}
