#ifndef REQUEST_H
#define REQUEST_H

#include <QUrl>
#include "types.h"

class Request
{
public:
    QString filePath;
    QUrl url;
    QString method;
    QByteArray body;
    Headers headers;
};

#endif // REQUEST_H
