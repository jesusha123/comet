#ifndef REQUESTSTORAGE_H
#define REQUESTSTORAGE_H

#include "request.h"
#include <QJsonArray>

class RequestStorage
{
public:
    RequestStorage();
    bool save(const Request& request);
    Request* read();
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // REQUESTSTORAGE_H
