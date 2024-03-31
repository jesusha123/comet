#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage();
    bool saveRequest(const Request& request, const QString name);
    bool deleteRequest(const Request& request);
    bool renameRequest(const Request& request, const QString newName);
    QList<Request> readCollection();
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // REQUESTSTORAGE_H
