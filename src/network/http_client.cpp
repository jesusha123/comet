#include "http_client.h"
#include <QtGlobal>
#include <curl/curl.h>
#include "response.h"
#include "curl_utils.h"
#include <QIODevice>
#include "http_method.h"

void HttpClient::sendRequest(Request& request)
{
    qInfo("Sending request");
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        Response response;

        enableDebugData(curl, response);

        curl_easy_setopt(curl, CURLOPT_URL, request.url.toString().toUtf8().data());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        QDataStream bodyDataStream(request.body);
        configureMethodAndBody(curl, request, bodyDataStream);

        auto list = addRequestHeaders(curl, request);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerFunction);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response);

        res = curl_easy_perform(curl);

        if(res == CURLE_OK) {
            qInfo("Successful request");
            addSuccessInfo(curl, response.info);
        } else {
            auto errorMessage = curl_easy_strerror(res);
            qInfo("Error sending request: %s", errorMessage);
            response.error.append(errorMessage);
        }

        // Clean up
        curl_easy_cleanup(curl);
        curl_slist_free_all(list);

        emit finished(response);
    } else {
        qCritical("Could not create a curl easy handle");
    }
}

/**
 * Configures HTTP method and body.
 *
 * This method combines both HTTP method and body because they go hand in hand. Setting the wrong body options
 * will make cURL send a different HTTP method than expected.
 */
void HttpClient::configureMethodAndBody(CURL* curl, Request& request, QDataStream& dataStream)
{
    auto methodKey = Http::OfficialMethods.indexOf(request.method);

    switch(methodKey) {
    case Http::GET:
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        break;
    case Http::POST:
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request.body.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.constData());
        break;
    case Http::PUT:
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readFunction);
        curl_easy_setopt(curl, CURLOPT_READDATA, &dataStream);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, request.body.size());
        break;
    case Http::PATCH:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.method.toUtf8().data());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request.body.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.constData());
        break;
    case Http::DEL:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.method.toUtf8().data());
        if(!request.body.isNull()) {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request.body.size());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.constData());
        }
        break;
    case Http::HEAD:
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        break;
    default:
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.method.toUtf8().data());
        break;
    }
}

void HttpClient::enableDebugData(CURL* curl, const Response& response)
{
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debugFunction);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &response);
}

curl_slist* HttpClient::addRequestHeaders(CURL* curl, const Request& request)
{
    struct curl_slist *list = NULL;

    for(const auto &header : request.headers) {
        QByteArray joinedHeader(header.first);
        if(header.second.isEmpty()) {
            // cURL requires a semi-colon for key-only headers
            joinedHeader.append(";");
        } else {
            joinedHeader.append(": ");
            joinedHeader.append(header.second);
        }
        list = curl_slist_append(list, joinedHeader.data());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    return list;
}

void HttpClient::addSuccessInfo(CURL* curl, Info& infoMap)
{
    addInfoStr(curl, CURLINFO_EFFECTIVE_URL, "EFFECTIVE_URL", infoMap);
    addInfoLong(curl, CURLINFO_RESPONSE_CODE, "RESPONSE_CODE", infoMap);
    addInfoDouble(curl, CURLINFO_TOTAL_TIME, "TOTAL_TIME", infoMap);
    addInfoDouble(curl, CURLINFO_NAMELOOKUP_TIME, "NAMELOOKUP_TIME", infoMap);
    addInfoDouble(curl, CURLINFO_CONNECT_TIME, "CONNECT_TIME", infoMap);
    addInfoDouble(curl, CURLINFO_PRETRANSFER_TIME, "PRETRANSFER_TIME", infoMap);
    addInfoOffT(curl, CURLINFO_SIZE_UPLOAD_T, "SIZE_UPLOAD_T", infoMap);
    addInfoOffT(curl, CURLINFO_SIZE_DOWNLOAD_T, "SIZE_DOWNLOAD_T", infoMap);
    addInfoOffT(curl, CURLINFO_SPEED_DOWNLOAD_T, "SPEED_DOWNLOAD_T", infoMap);
    addInfoOffT(curl, CURLINFO_SPEED_UPLOAD_T, "SPEED_UPLOAD_T", infoMap);
    addInfoLong(curl, CURLINFO_HEADER_SIZE, "HEADER_SIZE", infoMap);
    addInfoLong(curl, CURLINFO_REQUEST_SIZE, "REQUEST_SIZE", infoMap);
    addInfoLong(curl, CURLINFO_SSL_VERIFYRESULT, "SSL_VERIFYRESULT", infoMap);
    addInfoLong(curl, CURLINFO_FILETIME, "FILETIME", infoMap);
    addInfoOffT(curl, CURLINFO_FILETIME_T, "FILETIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, "CONTENT_LENGTH_DOWNLOAD_T", infoMap);
    addInfoOffT(curl, CURLINFO_CONTENT_LENGTH_UPLOAD_T, "CONTENT_LENGTH_UPLOAD_T", infoMap);
    addInfoDouble(curl, CURLINFO_STARTTRANSFER_TIME, "STARTTRANSFER_TIME", infoMap);
    addInfoStr(curl, CURLINFO_CONTENT_TYPE, "CONTENT_TYPE", infoMap);
    addInfoDouble(curl, CURLINFO_REDIRECT_TIME, "REDIRECT_TIME", infoMap);
    addInfoLong(curl, CURLINFO_REDIRECT_COUNT, "REDIRECT_COUNT", infoMap);
    addInfoStr(curl, CURLINFO_PRIVATE, "PRIVATE", infoMap);
    addInfoLong(curl, CURLINFO_HTTP_CONNECTCODE, "HTTP_CONNECTCODE", infoMap);
    addInfoLong(curl, CURLINFO_HTTPAUTH_AVAIL, "HTTPAUTH_AVAIL", infoMap);
    addInfoLong(curl, CURLINFO_PROXYAUTH_AVAIL, "PROXYAUTH_AVAIL", infoMap);
    addInfoLong(curl, CURLINFO_OS_ERRNO, "OS_ERRNO", infoMap);
    addInfoLong(curl, CURLINFO_NUM_CONNECTS, "NUM_CONNECTS", infoMap);
    addInfoNotImplemented(curl, CURLINFO_SSL_ENGINES, "SSL_ENGINES", infoMap);
    addInfoNotImplemented(curl, CURLINFO_COOKIELIST, "COOKIELIST", infoMap);
    addInfoStr(curl, CURLINFO_FTP_ENTRY_PATH, "FTP_ENTRY_PATH", infoMap);
    addInfoStr(curl, CURLINFO_REDIRECT_URL, "REDIRECT_URL", infoMap);
    addInfoStr(curl, CURLINFO_PRIMARY_IP, "PRIMARY_IP", infoMap);
    addInfoDouble(curl, CURLINFO_APPCONNECT_TIME, "APPCONNECT_TIME", infoMap);
    addInfoNotImplemented(curl, CURLINFO_CERTINFO, "CERTINFO", infoMap);
    addInfoLong(curl, CURLINFO_CONDITION_UNMET, "CONDITION_UNMET", infoMap);
    addInfoStr(curl, CURLINFO_RTSP_SESSION_ID, "RTSP_SESSION_ID", infoMap);
    addInfoLong(curl, CURLINFO_RTSP_CLIENT_CSEQ, "RTSP_CLIENT_CSEQ", infoMap);
    addInfoLong(curl, CURLINFO_RTSP_SERVER_CSEQ, "RTSP_SERVER_CSEQ", infoMap);
    addInfoLong(curl, CURLINFO_RTSP_CSEQ_RECV, "RTSP_CSEQ_RECV", infoMap);
    addInfoLong(curl, CURLINFO_PRIMARY_PORT, "PRIMARY_PORT", infoMap);
    addInfoStr(curl, CURLINFO_LOCAL_IP, "LOCAL_IP", infoMap);
    addInfoLong(curl, CURLINFO_LOCAL_PORT, "LOCAL_PORT", infoMap);
    addInfoNotImplemented(curl, CURLINFO_ACTIVESOCKET, "ACTIVESOCKET", infoMap);
    addInfoNotImplemented(curl, CURLINFO_TLS_SSL_PTR, "TLS_SSL_PTR", infoMap);
    addInfoLong(curl, CURLINFO_HTTP_VERSION, "HTTP_VERSION", infoMap);
    addInfoLong(curl, CURLINFO_PROXY_SSL_VERIFYRESULT, "PROXY_SSL_VERIFYRESULT", infoMap);
    addInfoStr(curl, CURLINFO_SCHEME, "SCHEME", infoMap);
    addInfoOffT(curl, CURLINFO_TOTAL_TIME_T, "TOTAL_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_NAMELOOKUP_TIME_T, "NAMELOOKUP_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_CONNECT_TIME_T, "CONNECT_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_PRETRANSFER_TIME_T, "PRETRANSFER_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_STARTTRANSFER_TIME_T, "STARTTRANSFER_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_REDIRECT_TIME_T, "REDIRECT_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_APPCONNECT_TIME_T, "APPCONNECT_TIME_T", infoMap);
    addInfoOffT(curl, CURLINFO_RETRY_AFTER, "RETRY_AFTER", infoMap);
    addInfoStr(curl, CURLINFO_EFFECTIVE_METHOD, "EFFECTIVE_METHOD", infoMap);
    addInfoLong(curl, CURLINFO_PROXY_ERROR, "PROXY_ERROR", infoMap);
    addInfoStr(curl, CURLINFO_REFERER, "REFERER", infoMap);
    addInfoStr(curl, CURLINFO_CAINFO, "CAINFO", infoMap);
    addInfoStr(curl, CURLINFO_CAPATH, "CAPATH", infoMap);
    addInfoOffT(curl, CURLINFO_XFER_ID, "XFER_ID", infoMap);
    addInfoOffT(curl, CURLINFO_CONN_ID, "CONN_ID", infoMap);
}

void HttpClient::addInfoDouble(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info)
{
    double n;
    curl_easy_getinfo(curl, curlInfo, &n);
    info.append(qMakePair(infoName, QString::number(n)));
}

void HttpClient::addInfoLong(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info)
{
    long n;
    curl_easy_getinfo(curl, curlInfo, &n);
    info.append(qMakePair(infoName, QString::number(n)));
}

void HttpClient::addInfoOffT(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info)
{
    curl_off_t n;
    curl_easy_getinfo(curl, curlInfo, &n);
    info.append(qMakePair(infoName, QString::number(n)));
}

void HttpClient::addInfoStr(CURL* curl, CURLINFO curlInfo, const char* infoName, Info& info)
{
    char* s = NULL;
    curl_easy_getinfo(curl, curlInfo, &s);
    auto value = QString();
    if (s) {
        value = s;
    }
    info.append(qMakePair(infoName, s));
}

void HttpClient::addInfoNotImplemented(CURL*, CURLINFO, const char* infoName, Info& info)
{
    info.append(qMakePair(infoName, ""));
}
