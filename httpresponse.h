#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QList>
#include "types.h"

class HttpResponse
{
public:
    QByteArray body;
    QString statusLine;
    QString error;
    Headers headers;
    DebugInfo debugInfo;
};

#endif // HTTPRESPONSE_H
