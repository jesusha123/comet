#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage() = delete;

    static bool loadRequest(Request &request);
    static bool saveRequest(const Request &request);
    static bool deleteRequest(const QString &filePath);
    static bool renameRequest(const QString &prevFilePath, const QString &newFilePath);
};

#endif // REQUESTSTORAGE_H
