#include "RequestBuilder.h"
#include "ui_requestwidget.h"
#include <QUrlQuery>

Request RequestBuilder::buildRequest(std::unique_ptr<Ui::RequestWidget>& ui)
{
    Request request;
    request.url.setUrl(ui->urlLineEdit->text(), QUrl::StrictMode);
    request.method = ui->methodComboBox->currentText();

    addBody(ui, request);
    addRequestHeaders(ui, request);

    return request;
}

void RequestBuilder::addBody(std::unique_ptr<Ui::RequestWidget>& ui, Request& request)
{
    if(Http::hasRequestBody(static_cast<Http::Method>(ui->methodComboBox->currentIndex()))) {
        auto contentType = ui->reqContentTypeComboBox->currentText();

        if(contentType.compare("application/x-www-form-urlencoded") == 0 || contentType.compare("multipart/form-data") == 0) {
            request.headers.append(qMakePair("Content-Type", contentType.toUtf8()));
            QUrlQuery query;

            for(const auto& propertyPair : ui->reqBodyTableWidget->getProperties()) {
                query.addQueryItem(propertyPair.first, propertyPair.second);
            }

            request.body.append(query.toString().toUtf8());
        } else if(contentType.compare("none") != 0) {
            request.body.append(ui->reqBodyTextWidget->toPlainText().toUtf8());
            request.headers.append(qMakePair("Content-Type", contentType.toUtf8()));
        }
    }
}

void RequestBuilder::addRequestHeaders(std::unique_ptr<Ui::RequestWidget>& ui, Request& request)
{
    for(const auto& propertyPair : ui->requestHeadersTableWidget->getProperties()) {
        request.headers.append(qMakePair(propertyPair.first.toUtf8(), propertyPair.second.toUtf8()));
    }
}

void RequestBuilder::restoreRequest(std::unique_ptr<Ui::RequestWidget>& ui, const Request& request)
{
    ui->urlLineEdit->setText(request.url.toString());
    ui->methodComboBox->setCurrentText(request.method);

    ui->requestHeadersTableWidget->setRowCount(request.headers.count()+1); // +1 for the new empty row
    int i = 0;
    for(const auto &header : request.headers) {
        ui->requestHeadersTableWidget->setProperty(i++, header.first, header.second);
    }
}
