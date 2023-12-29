#include "httpclient.h"
#include <QtGlobal>
#include <curl/curl.h>
#include "httpresponse.h"
#include "curlutils.h"

void HttpClient::sendRequest(const HttpRequest& request)
{
    qInfo("Sending request");
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        HttpResponse response;
        struct curl_slist *list = NULL;

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, debugFunction);
        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &response);

        curl_easy_setopt(curl, CURLOPT_URL, request.url.toString().toUtf8().data());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.method.toUtf8().data());

        for(const auto &header : request.headers) {
            QByteArray joinedHeader(header.first);
            if(header.second.isEmpty()) {
                joinedHeader.append(";");
            } else {
                joinedHeader.append(": ");
                joinedHeader.append(header.second);
            }
            list = curl_slist_append(list, joinedHeader.data());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request.body.size());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.body.constData());

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
