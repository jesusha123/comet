#include "collection_storage.h"
#include <QApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CollectionStorage::CollectionStorage()
{
}

Collection* CollectionStorage::loadFromFile(const QString& filePath)
{
    qInfo("Loading collection from file %s", qPrintable(filePath));
    Collection* collection = nullptr;

    QFile dataFile(filePath);

    if (dataFile.open(QIODevice::ReadOnly)) {
        qInfo("File opened successfully");

        QByteArray data = dataFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
        auto root = jsonDoc.object();

        auto name = root["info"].toObject()["name"].toString();
        collection = new Collection(name);

        auto itemArray = root["item"].toArray();

        for(const auto& itemValue : itemArray) {
            auto item = itemValue.toObject();
            auto itemRequest = item["request"].toObject();
            Request* request = new Request();

            request->name = item["name"].toString();
            request->url.setUrl(itemRequest["url"].toObject()["raw"].toString());
            request->method = itemRequest["method"].toString();

            collection->append(request);
        }
        qInfo("Finished loading collection from data file.");
    } else {
        qWarning("Couldn't open read file.");
    }

    return collection;
}
