#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "types.h"

class HttpResponse
{
public:
    QByteArray body;
    QString statusLine;
    QString error;
    Headers headers;
    DebugInfo debugInfo;
    Info info;
};

#endif // HTTPRESPONSE_H
