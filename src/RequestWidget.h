#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QUuid>
#include "Request.h"
#include "HttpClient.h"
#include "HttpMethod.h"
#include "ui_requestwidget.h"

class RequestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestWidget(std::shared_ptr<HttpClient> httpClient, QWidget* parent, QString name = QString());
    Request getRequest();
    void restoreRequest(const Request& request);
    QString getName() { return name; }
    void setName(QString newName) { name = newName; }

private slots:
    void sendRequest();
    void processResponse(const Response& response);
    void processParams(const QString& url);
    void processParamsChanged(QTableWidgetItem *item);
    void processParamsRemoved();
    void processRequestBodyAllowed(Http::HasBody reqHasBody);
    void processReqContentTypeChange(int index);

private:
    void buildParamsLineEdit();
    void initializeConnections();

    std::unique_ptr<Ui::RequestWidget> ui;
    std::shared_ptr<HttpClient> httpClient;
    QString name;
};

#endif
