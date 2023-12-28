#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "httprequest.h"
#include "httpresponse.h"

class HttpClient : public QObject
{
    Q_OBJECT
public:
    void sendRequest(const HttpRequest& request);
signals:
    void finished(const HttpResponse response);
};

#endif // HTTPCLIENT_H
