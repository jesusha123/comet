#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include "Request.h"
#include "HttpClient.h"
#include "HttpMethod.h"

namespace Ui {
class RequestWidget;
}

class RequestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RequestWidget(HttpClient* httpClient, QWidget* parent = nullptr);
    ~RequestWidget();

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

    Ui::RequestWidget* ui;
    HttpClient* httpClient;
};

#endif
