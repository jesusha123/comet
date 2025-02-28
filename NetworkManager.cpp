#include "NetworkManager.h"
#include <QNetworkReply>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
}

void NetworkManager::sendRequest(Request *request, Response *response)
{
    QUrl url(request->url());
    QNetworkRequest networkRequest(url);

    QNetworkReply *reply = nullptr;
    reply = m_manager.get(networkRequest);

    connect(reply, &QNetworkReply::finished, this, [reply, response]() {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray data = reply->readAll();

        response->setStatusCode(statusCode);
        response->setBody(QString::fromUtf8(data));

        reply->deleteLater();
    });
}
