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

        // Deserialize headers
        if (node["headers"]) {
            YAML::Node headersNode = node["headers"];
            // Clear the current headersModel contents.
            request->headersModel()->clear();

            for (std::size_t i = 0; i < headersNode.size(); ++i) {
                YAML::Node header = headersNode[i];
                if (header["key"] && header["value"]) {
                    QString key = QString::fromStdString(header["key"].as<std::string>());
                    QString value = QString::fromStdString(header["value"].as<std::string>());
                    // Create a new row with two items: key and value.
                    QList<QStandardItem*> row;
                    row << new QStandardItem(key) << new QStandardItem(value);
                    request->headersModel()->appendRow(row);
                }
            }
        }
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

    // Serialize headers from the headersModel
    out << YAML::Key << "headers" << YAML::Value << YAML::BeginSeq;
    int rowCount = request->headersModel()->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QStandardItem* keyItem = request->headersModel()->item(row, 0);
        QStandardItem* valueItem = request->headersModel()->item(row, 1);
        if (keyItem && valueItem) {
            out << YAML::BeginMap;
            out << YAML::Key << "key" << YAML::Value << keyItem->text().toStdString();
            out << YAML::Key << "value" << YAML::Value << valueItem->text().toStdString();
            out << YAML::EndMap;
        }
    }
    out << YAML::EndSeq;

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
