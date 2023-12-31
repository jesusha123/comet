#include "requestbuilder.h"
#include "ui_mainwindow.h"

RequestBuilder::RequestBuilder(Ui::MainWindow* ui)
    : ui(ui)
{
}

HttpRequest RequestBuilder::buildRequest()
{
    HttpRequest request;
    request.url.setUrl(ui->urlLineEdit->text(), QUrl::StrictMode);
    request.method = ui->methodComboBox->currentText();

    if(ui->reqBodyComboBox->currentText().compare("None") != 0) {
        request.body.append(ui->requestBodyPlainTextEdit->toPlainText().toUtf8());
    }

    addRequestHeaders(request);

    return request;
}


void RequestBuilder::addRequestHeaders(HttpRequest& request)
{
    for(const auto& propertyPair : ui->requestHeadersTableWidget->getProperties()) {
        request.headers.append(qMakePair(propertyPair.first.toUtf8(), propertyPair.second.toUtf8()));
    }
}
