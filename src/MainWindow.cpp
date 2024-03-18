#include "MainWindow.h"
#include "ui_main_window.h"
#include <QDateTime>
#include "HttpClient.h"
#include "DebugInfoFormatter.h"
#include <QUrlQuery>
#include "RequestBuilder.h"
#include "ContentTypeComboBox.h"
#include <QMessageBox>

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

    ui->statusBar->showMessage("Ready");

    // Initial method is GET, so hide body tab.
    ui->requestTabWidget->setTabVisible(2, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    RequestBuilder builder(ui);
    auto request = builder.buildRequest();
    httpClient->sendRequest(request);
}

void MainWindow::processResponse(const Response& response)
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

    connect(ui->reqContentTypeComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::processReqContentTypeChange);

    connect(ui->addReqParamButton, &QToolButton::clicked, ui->requestParamsTableWidget, &PropertyTableWidget::appendRow);
    connect(ui->removeReqParamButton, &QToolButton::clicked, ui->requestParamsTableWidget, &PropertyTableWidget::removeSelectedRows);
    connect(ui->requestParamsTableWidget, &QTableWidget::itemChanged, this, &MainWindow::processParamsChanged);
    connect(ui->requestParamsTableWidget, &PropertyTableWidget::rowsRemoved, this, &MainWindow::processParamsRemoved);

    connect(ui->addReqHeaderButton, &QToolButton::clicked, ui->requestHeadersTableWidget, &PropertyTableWidget::appendRow);
    connect(ui->removeReqHeaderButton, &QToolButton::clicked, ui->requestHeadersTableWidget, &PropertyTableWidget::removeSelectedRows);

    connect(ui->addReqBodyPropButton, &QToolButton::clicked, ui->reqBodyTableWidget, &PropertyTableWidget::appendRow);
    connect(ui->removeReqBodyPropButton, &QToolButton::clicked, ui->reqBodyTableWidget, &PropertyTableWidget::removeSelectedRows);

    connect(ui->methodComboBox, &MethodComboBox::requestBodyAllowed, this, &MainWindow::processRequestBodyAllowed);

    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

void MainWindow::processReqContentTypeChange(int)
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

void MainWindow::processRequestBodyAllowed(Http::HasBody hasBody)
{
    ui->requestTabWidget->setTabVisible(2, hasBody != Http::No);
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, "Comet",
                       "<h1>Comet</h1>"
                       "<p>Version 0.0.1</p>"
                       "<p>Powered by open source software:</p>"
                       "<p>Qt 6 | License: <a href='https://doc.qt.io/qt-6/lgpl.html'>LGPL</a></p>"
                       "<p>libcurl | License: <a href='https://curl.se/docs/copyright.html'>curl license</a></p>"
                       );
}
