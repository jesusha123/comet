#include "RequestFileManager.h"
#include <QFile>
#include <yaml-cpp/yaml.h>

RequestFileManager::RequestFileManager(QObject *parent)
    : QObject(parent)
{
}

void RequestFileManager::loadRequestFromFile(const QString &filePath, Request *request) {
    if (!request) {
        qWarning() << "Request pointer is null!";
        return;
    }

    try {
        YAML::Node node = YAML::LoadFile(filePath.toStdString());

        // Update the Request object if keys exist in the YAML
        if (node["url"])
            request->setUrl(QString::fromStdString(node["url"].as<std::string>()));
        if (node["method"])
            request->setMethod(QString::fromStdString(node["method"].as<std::string>()));
        if (node["body"])
            request->setBody(QString::fromStdString(node["body"].as<std::string>()));
    } catch (const YAML::Exception &e) {
        qWarning() << "Failed to load or parse YAML file:" << filePath << "\nError:" << e.what();
    }
}

Q_INVOKABLE bool RequestFileManager::saveRequestToFile(const QString &filePath, Request *request) {
    if (!request) {
        qWarning() << "Request pointer is null!";
        return false;
    }

    // Use YAML::Emitter to construct the YAML content.
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "url" << YAML::Value << request->url().toStdString();
    out << YAML::Key << "method" << YAML::Value << request->method().toStdString();
    out << YAML::Key << "body" << YAML::Value << request->body().toStdString();
    out << YAML::EndMap;

    // Write the YAML string to a file.
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << filePath;
        return false;
    }
    file.write(out.c_str());
    file.close();
    return true;
}
