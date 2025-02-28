#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QObject>
#include "Request.h"
#include "Response.h"

class NetworkManager : public QObject {
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(Request *request, Response *response);
private:
    QNetworkAccessManager m_manager;
};

#endif
