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
    explicit RequestWidget(QWidget* parent, QString name = QString());
    Request getRequest();
    void restoreRequest(const Request& request);
    QString getRequestFilePath() { return requestFilePath; }
    void setRequestFilePath(QString requestFilePath) { this->requestFilePath = requestFilePath; }

private slots:
    void sendRequest();
    void processResponse(const Response response);
    void processParams(const QString url);
    void processParamsChanged(QTableWidgetItem *item);
    void processParamsRemoved();
    void processRequestBodyAllowed(Http::HasBody reqHasBody);
    void processReqContentTypeChange(int index);

private:
    void buildParamsLineEdit();
    void initializeConnections();

    std::unique_ptr<Ui::RequestWidget> ui;
    QString requestFilePath;
};

#endif
