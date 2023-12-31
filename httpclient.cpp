#include "httpclient.h"
#include <QtGlobal>
#include <curl/curl.h>
#include "httpresponse.h"
#include "curlutils.h"
#include <QIODevice>
#include "httpmethod.h"

void HttpClient::sendRequest(HttpRequest& request)
{
    qInfo("Sending request");
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        HttpResponse response;

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
void HttpClient::configureMethodAndBody(CURL* curl, HttpRequest& request, QDataStream& dataStream)
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
    case Http::DELETE:
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

void HttpClient::enableDebugData(CURL* curl, const HttpResponse& response)
{
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debugFunction);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &response);
}

curl_slist* HttpClient::addRequestHeaders(CURL* curl, const HttpRequest& request)
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
