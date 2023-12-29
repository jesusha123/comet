#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QList>
#include "debuginfo.h"

class HttpResponse
{
public:
    QByteArray body;
    QString statusLine;
    QString error;
    QList<QPair<QByteArray, QByteArray>> headers;
    DebugInfo debugInfo;
};

#endif // HTTPRESPONSE_H
