#ifndef HTTPREQUESTSTORAGE_H
#define HTTPREQUESTSTORAGE_H

#include "httprequest.h"
#include <QJsonArray>

class HttpRequestStorage
{
public:
    HttpRequestStorage();
    bool save(const HttpRequest& request);
    HttpRequest* read();
private:
    QJsonArray getJsonHeaders(const HttpRequest& request);

    QString appDataDirectory;
};

#endif // HTTPREQUESTSTORAGE_H
