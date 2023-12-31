#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "httpclient.h"
#include "httprequest.h"
#include "debuginfoformatter.h"
#include <QUrlQuery>
#include "httpmethod.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , httpClient(new HttpClient)
{
    ui->setupUi(this);

    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(QApplication::font().pointSize());
    ui->debugPlainTextEdit->setFont(fixedFont);

    ui->responseHeadersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    initializeConnections();
    initializeHeaderTables();
    initializeMethodComboBox();

    ui->statusBar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    HttpRequest request;
    request.url.setUrl(ui->urlLineEdit->text(), QUrl::StrictMode);
    request.method = ui->methodComboBox->currentText();

    if(ui->reqBodyComboBox->currentText().compare("None") != 0) {
      request.body.append(ui->requestBodyPlainTextEdit->toPlainText().toUtf8());
    }

    addRequestHeaders(request);
    httpClient->sendRequest(request);
}

void MainWindow::processResponse(const HttpResponse& response)
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
    ui->statusBar->showMessage(statusMessage);

    ui->infoTableWidget->setRowCount(response.info.size());
    int row = 0;
    for(const auto& pair : response.info) {
        ui->infoTableWidget->setProperty(row++, pair.first, pair.second);
    }
}

void MainWindow::processParams(const QString& url)
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

void MainWindow::processParamsChanged(QTableWidgetItem *)
{
    buildParamsLineEdit();
}

void MainWindow::processParamsRemoved()
{
    buildParamsLineEdit();
}

void MainWindow::buildParamsLineEdit()
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

void MainWindow::initializeConnections()
{
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendRequest);
    connect(httpClient, &HttpClient::finished, this, &MainWindow::processResponse);
    connect(ui->urlLineEdit, &QLineEdit::textEdited, this, &MainWindow::processParams);

    connect(ui->reqBodyComboBox, &QComboBox::activated, ui->reqBodyStackedWidget, &QStackedWidget::setCurrentIndex);

    connect(ui->addReqParamButton, &QToolButton::clicked, ui->requestParamsTableWidget, &PropertyTableWidget::appendRow);
    connect(ui->removeReqParamButton, &QToolButton::clicked, ui->requestParamsTableWidget, &PropertyTableWidget::removeSelectedRows);
    connect(ui->requestParamsTableWidget, &QTableWidget::itemChanged, this, &MainWindow::processParamsChanged);
    connect(ui->requestParamsTableWidget, &PropertyTableWidget::rowsRemoved, this, &MainWindow::processParamsRemoved);

    connect(ui->addReqHeaderButton, &QToolButton::clicked, ui->requestHeadersTableWidget, &PropertyTableWidget::appendRow);
    connect(ui->removeReqHeaderButton, &QToolButton::clicked, ui->requestHeadersTableWidget, &PropertyTableWidget::removeSelectedRows);
}

void MainWindow::initializeHeaderTables()
{
    ui->responseHeadersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::initializeMethodComboBox()
{
    ui->methodComboBox->addItems(Http::OfficialMethods);
}

void MainWindow::addRequestHeaders(HttpRequest& request)
{
    for(int rowIndex=0; rowIndex < ui->requestHeadersTableWidget->rowCount(); rowIndex++) {
        auto keyItem = ui->requestHeadersTableWidget->item(rowIndex, 0);

        if(keyItem) {
            auto keyText = keyItem->text();
            if(!keyText.isEmpty()) {
                // Initialize QByteArray with empty string to avoid processing a null QByteArray
                QByteArray valueText("");

                auto valueItem = ui->requestHeadersTableWidget->item(rowIndex, 1);
                if (valueItem) {
                    valueText.append(valueItem->text().toUtf8());
                }

                request.headers.append(qMakePair(keyText.toUtf8(), valueText));
            }
        }
    }
}
