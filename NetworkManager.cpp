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

    QString method = request->method();
    QNetworkReply *reply = nullptr;

    QByteArray body = request->body().toUtf8();

    if (method == "GET") {
        reply = m_manager.get(networkRequest, body);
    } else if (method == "POST") {
        reply = m_manager.post(networkRequest, body);
    } else if (method == "PUT") {
        reply = m_manager.put(networkRequest, body);
    } else if (method == "DELETE") {
        reply = m_manager.deleteResource(networkRequest);
    } else if (method == "PATCH") {
        reply = m_manager.sendCustomRequest(networkRequest, "PATCH", body);
    } else if (method == "OPTIONS") {
        reply = m_manager.sendCustomRequest(networkRequest, "OPTIONS", body);
    } else if (method == "HEAD") {
        reply = m_manager.head(networkRequest);
    } else {
        return;
    }

    connect(reply, &QNetworkReply::finished, this, [reply, response]() {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QByteArray data = reply->readAll();

        response->setStatusCode(statusCode);
        response->setBody(QString::fromUtf8(data));

        TableModel* model = response->headersModel();
        model->removeRows(0, model->rowCount());
        const QList<QByteArray> headerList = reply->rawHeaderList();
        for (const QByteArray &headerName : headerList) {
            QByteArray headerValue = reply->rawHeader(headerName);
            QList<QStandardItem*> row;
            row << new QStandardItem(QString::fromUtf8(headerName))
                << new QStandardItem(QString::fromUtf8(headerValue));
            model->appendRow(row);
        }

        reply->deleteLater();
    });
}
