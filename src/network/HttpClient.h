#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "Request.h"
#include "Response.h"

class HttpClient : public QObject
{
    Q_OBJECT
public:
    Response sendRequest(Request& request);
private:
    void configureMethodAndBody(CURL* curl, Request& request, QDataStream& dataStream);
    void enableDebugData(CURL* curl, const Response& response);
    curl_slist* addRequestHeaders(CURL* curl, const Request& request);
    void addSuccessInfo(CURL* curl, Info& info);
    void addInfoDouble(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoLong(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoOffT(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoStr(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
    void addInfoNotImplemented(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info);
};

#endif // HTTPCLIENT_H
