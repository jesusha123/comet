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
