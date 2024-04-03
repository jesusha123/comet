#include "RequestThread.h"
#include "HttpClient.h"

RequestThread::RequestThread(const Request& request, QObject* parent)
    : request(request)
    , QThread(parent)
{
}

void RequestThread::run() {
    HttpClient client;
    auto response = client.sendRequest(request);
    emit responseReady(response);
}
