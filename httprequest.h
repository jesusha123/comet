#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QUrl>

class HttpRequest
{
public:
    QUrl url;
    QString method;
    QByteArray body;
    QList<QPair<QByteArray, QByteArray>> headers;
};

#endif // HTTPREQUEST_H
