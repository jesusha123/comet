#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage();

    Request loadRequest(const QString &filePath);
    bool saveRequest(const Request& request, const QString name);
    bool deleteRequest(const Request& request);
    bool renameRequest(const Request& request, const QString newName);
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // REQUESTSTORAGE_H
