#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage();
    bool saveRequest(const Request& request, const QString name);
    QList<Request> readCollection();
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // REQUESTSTORAGE_H
