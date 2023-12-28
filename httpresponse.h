#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QList>

class HttpResponse
{
public:
    QByteArray body;
    QString statusLine;
    QString error;
    QList<QPair<QByteArray, QByteArray>> headers;
};

#endif // HTTPRESPONSE_H
