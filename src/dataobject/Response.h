#ifndef RESPONSE_H
#define RESPONSE_H

#include "types.h"

class Response
{
public:
    QByteArray body;
    QString statusLine;
    QString error;
    Headers headers;
    DebugInfo debugInfo;
    Info info;
};

#endif // RESPONSE_H
