#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "httprequest.h"
#include "httpresponse.h"

class HttpClient : public QObject
{
    Q_OBJECT
public:
    void sendRequest(HttpRequest& request);
signals:
    void finished(const HttpResponse response);
private:
    void configureMethodAndBody(CURL* curl, HttpRequest& request, QDataStream& dataStream);
    void enableDebugData(CURL* curl, const HttpResponse& response);
    curl_slist* addRequestHeaders(CURL* curl, const HttpRequest& request);
    void addSuccessInfo(CURL* curl, Info& info);
    void addInfoDouble(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoLong(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoOffT(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoStr(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoNotImplemented(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
};

#endif // HTTPCLIENT_H
