#include "RequestBuilder.h"
#include "ui_main_window.h"
#include <QUrlQuery>

RequestBuilder::RequestBuilder(Ui::MainWindow* ui)
    : ui(ui)
{
}

Request RequestBuilder::buildRequest()
{
    Request request;
    request.url.setUrl(ui->urlLineEdit->text(), QUrl::StrictMode);
    request.method = ui->methodComboBox->currentText();

    addBody(request);
    addRequestHeaders(request);

    return request;
}

void RequestBuilder::addBody(Request& request)
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

void RequestBuilder::addRequestHeaders(Request& request)
{
    for(const auto& propertyPair : ui->requestHeadersTableWidget->getProperties()) {
        request.headers.append(qMakePair(propertyPair.first.toUtf8(), propertyPair.second.toUtf8()));
    }
}

void RequestBuilder::restoreRequest(const Request& request)
{
    ui->urlLineEdit->setText(request.url.toString());

    ui->requestHeadersTableWidget->setRowCount(request.headers.count());
    int i = 0;
    for(const auto &header : request.headers) {
        ui->requestHeadersTableWidget->setProperty(i++, header.first, header.second);
    }
}
