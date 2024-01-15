#ifndef HTTPREQUESTSTORAGE_H
#define HTTPREQUESTSTORAGE_H

#include "Request.h"
#include <QJsonArray>

class HttpRequestStorage
{
public:
    HttpRequestStorage();
    bool save(const Request& request);
    Request* read();
private:
    QJsonArray getJsonHeaders(const Request& request);

    QString appDataDirectory;
};

#endif // HTTPREQUESTSTORAGE_H
