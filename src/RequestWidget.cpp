#include "RequestWidget.h"
#include "DebugInfoFormatter.h"
#include "RequestBuilder.h"
#include "RequestThread.h"
#include <QDateTime>
#include <QUrlQuery>

RequestWidget::RequestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RequestWidget)
{
    ui->setupUi(this);

    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(QApplication::font().pointSize());
    ui->debugPlainTextEdit->setFont(fixedFont);

    ui->responseHeadersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Initial method is GET, so hide body tab.
    ui->requestTabWidget->setTabVisible(2, false);

    initializeConnections();
}

Request RequestWidget::getRequest()
{
    Request request = RequestBuilder::buildRequest(ui);
    request.filePath = requestFilePath;
    return request;
}

void RequestWidget::restoreRequest(const Request& request)
{
    RequestBuilder::restoreRequest(ui, request);
}

void RequestWidget::sendRequest()
{
    auto request = RequestBuilder::buildRequest(ui);

    RequestThread *requestThread = new RequestThread(request, this);
    connect(requestThread, &RequestThread::responseReady, this, &RequestWidget::processResponse);
    connect(requestThread, &RequestThread::finished, requestThread, &QObject::deleteLater);
    requestThread->start();
}

void RequestWidget::processResponse(const Response response)
{
    qInfo("Processing response");
    ui->responseBodyPlainTextEdit->setPlainText(response.body.data());

    auto headerCount = response.headers.count();
    auto headersTableWidget = ui->responseHeadersTableWidget;
    headersTableWidget->clearContents();
    headersTableWidget->setRowCount(headerCount);

    for(int rowIndex=0; rowIndex<headerCount; rowIndex++) {
        auto header = response.headers.at(rowIndex);
        headersTableWidget->setItem(rowIndex, 0, new QTableWidgetItem(header.first));
        headersTableWidget->setItem(rowIndex, 1, new QTableWidgetItem(header.second));
    }

    DebugInfoFormatter formatter(response.debugInfo);
    ui->debugPlainTextEdit->setPlainText(formatter.toString());

    auto statusMessage = QString("%1%2 [%3]").arg(response.statusLine, response.error, QDateTime::currentDateTime().toString());

    ui->infoTableWidget->setRowCount(response.info.size());
    int row = 0;
    for(const auto& pair : response.info) {
        ui->infoTableWidget->setProperty(row++, pair.first, pair.second);
    }
}

void RequestWidget::processParams(const QString url)
{
    auto urlObject = QUrl(url);
    if(urlObject.hasQuery()) {
        auto queryItems = QUrlQuery(urlObject).queryItems();
        ui->requestParamsTableWidget->setRowCount(queryItems.count());

        ui->requestParamsTableWidget->blockSignals(true);
        for(int i=0; i<queryItems.count(); i++) {
            auto queryItem = queryItems.at(i);
            ui->requestParamsTableWidget->setProperty(i, queryItem.first, queryItem.second);
        }
        ui->requestParamsTableWidget->blockSignals(false);

    } else {
        ui->requestParamsTableWidget->setRowCount(0);
    }
}

void RequestWidget::buildParamsLineEdit()
{
    auto url = QUrl(ui->urlLineEdit->text());
    auto urlQuery = QUrlQuery();

    for(int rowIndex=0; rowIndex < ui->requestParamsTableWidget->rowCount(); rowIndex++) {
        auto keyItem = ui->requestParamsTableWidget->item(rowIndex, 0);
        auto keyText = keyItem ? keyItem->text() : QString();

        auto valueItem = ui->requestParamsTableWidget->item(rowIndex, 1);
        auto valueText = valueItem ? valueItem->text() : QString();

        urlQuery.addQueryItem(keyText, valueText);
    }

    url.setQuery(urlQuery);
    ui->urlLineEdit->setText(url.toString());
}

void RequestWidget::processParamsChanged(QTableWidgetItem *)
{
    buildParamsLineEdit();
}

void RequestWidget::processParamsRemoved()
{
    buildParamsLineEdit();
}

void RequestWidget::processReqContentTypeChange(int)
{
    auto contentType = ui->reqContentTypeComboBox->currentText();
    if(contentType.compare("none") == 0) {
        ui->reqBodyStackedWidget->setCurrentIndex(0);
    } else if(contentType.compare("application/x-www-form-urlencoded") == 0 || contentType.compare("multipart/form-data") == 0) {
        ui->reqBodyStackedWidget->setCurrentIndex(2);
    } else {
        ui->reqBodyStackedWidget->setCurrentIndex(1);
    }
}

void RequestWidget::processRequestBodyAllowed(Http::HasBody hasBody)
{
    ui->requestTabWidget->setTabVisible(2, hasBody != Http::No);
}

void RequestWidget::initializeConnections()
{
    connect(ui->sendButton, &QPushButton::clicked, this, &RequestWidget::sendRequest);
    connect(ui->urlLineEdit, &QLineEdit::textEdited, this, &RequestWidget::processParams);

    connect(ui->reqContentTypeComboBox, &QComboBox::currentIndexChanged, this, &RequestWidget::processReqContentTypeChange);

    connect(ui->requestParamsTableWidget, &QTableWidget::itemChanged, this, &RequestWidget::processParamsChanged);
    // TODO, handle scenario where removing rows should trigger RequestWidget::processParamsRemoved

    connect(ui->methodComboBox, &MethodComboBox::requestBodyAllowed, this, &RequestWidget::processRequestBodyAllowed);
}
