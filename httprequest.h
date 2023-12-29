#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QUrl>
#include "types.h"

class HttpRequest
{
public:
    QUrl url;
    QString method;
    QByteArray body;
    Headers headers;
};

#endif // HTTPREQUEST_H
