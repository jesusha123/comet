#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include "Request.h"
#include "HttpClient.h"
#include "HttpMethod.h"
#include "ui_requestwidget.h"

class RequestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestWidget(std::shared_ptr<HttpClient> httpClient, QWidget* parent = nullptr);

signals:
    void saveRequestTriggered();

private slots:
    void sendRequest();
    void processResponse(const Response& response);
    void processParams(const QString& url);
    void processParamsChanged(QTableWidgetItem *item);
    void processParamsRemoved();
    void processRequestBodyAllowed(Http::HasBody reqHasBody);
    void processReqContentTypeChange(int index);
    void saveButtonClicked();

private:
    void buildParamsLineEdit();
    void initializeConnections();

    std::unique_ptr<Ui::RequestWidget> ui;
    std::shared_ptr<HttpClient> httpClient;
};

#endif
