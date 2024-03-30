#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage();
    bool save(const Request& request, const QString fileName);
    Request* read();
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // REQUESTSTORAGE_H
