#include "RequestStorage.h"
#include <QApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <yaml-cpp/yaml.h>

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

bool RequestStorage::deleteRequest(const Request &request)
{
    QFile file (appDataDirectory + "/" + request.name + ".json");
    return file.remove();
}

bool RequestStorage::renameRequest(const Request &request, const QString newName)
{
    QFile file (appDataDirectory + "/" + request.name + ".json");
    return file.rename(appDataDirectory + "/" + newName + ".json");
}

QList<Request> RequestStorage::readCollection(QString workspacePath)
{
    qInfo() << "Reading collection from workspace: " << workspacePath;
    QList<Request> list;
    QStringList yamlFiles = getYamlFiles(workspacePath);
    qInfo() << "Found yaml files: " << yamlFiles;

    for (const QString &yamlFile : yamlFiles) {
        qInfo() << "Loading yaml file: " << yamlFile;
        Request request = loadRequest(yamlFile);
        list.append(request);
    }

    return list;
}

QStringList RequestStorage::getYamlFiles(const QString &directoryPath)
{
    QDir directory(directoryPath);
    directory.setFilter(QDir::Files);

    QStringList nameFilters;
    nameFilters << "*.yaml" << "*.yml";

    QStringList yamlFiles = directory.entryList(nameFilters, QDir::Files);

    QStringList fullPaths;
    for (const QString &file : yamlFiles) {
        fullPaths << directory.absoluteFilePath(file);
    }

    return fullPaths;
}

Request RequestStorage::loadRequest(const QString &filePath)
{
    Request request;

    // Load the YAML file
    YAML::Node yamlNode = YAML::LoadFile(filePath.toStdString());

    // Map YAML content to the Request class
    QFileInfo fileInfo(filePath);
    request.name = fileInfo.baseName();

    if (yamlNode["url"]) {
        request.url = QUrl(QString::fromStdString(yamlNode["url"].as<std::string>()));
        qInfo() << "url: " << request.url;
    }

    if (yamlNode["method"]) {
        request.method = QString::fromStdString(yamlNode["method"].as<std::string>());
        qInfo() << "method: " << request.method;
    }

    if (yamlNode["body"]) {
        request.body = QByteArray::fromStdString(yamlNode["body"].as<std::string>());
        qInfo() << "body: " << request.body;
    }

    if (yamlNode["headers"]) {
        YAML::Node headersNode = yamlNode["headers"];
        for (YAML::const_iterator it = headersNode.begin(); it != headersNode.end(); ++it) {
            QString key = QString::fromStdString(it->first.as<std::string>());
            QString value = QString::fromStdString(it->second.as<std::string>());
            request.headers.append(qMakePair(key, value));
        }
    }

    return request;
}
