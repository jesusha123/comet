#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "httpclient.h"
#include "httprequest.h"
#include "debuginfoformatter.h"
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , httpClient(new HttpClient)
{
    ui->setupUi(this);

    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(QApplication::font().pointSize());
    ui->debugPlainTextEdit->setFont(fixedFont);

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
    request.body.append(ui->requestBodyPlainTextEdit->toPlainText().toUtf8());
    addRequestHeaders(request);
    httpClient->sendRequest(request);
}

void MainWindow::processResponse(const HttpResponse response)
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
}

void MainWindow::processParams(const QString& url)
{
    auto urlObject = QUrl(url);
    if(urlObject.hasQuery()) {
        auto queryItems = QUrlQuery(urlObject).queryItems();
        ui->requestParamsTableWidget->setRowCount(queryItems.count());
        qInfo("Table rows: %d, cols: %d", ui->requestParamsTableWidget->rowCount(), ui->requestParamsTableWidget->columnCount());

        for(int i=0; i<queryItems.count(); i++) {
            qInfo(" Inserting at row: %d", i);
            auto queryItem = queryItems.at(i);
            ui->requestParamsTableWidget->setProperty(i, queryItem.first, queryItem.second);
        }
    } else {
        ui->requestParamsTableWidget->setRowCount(0);
    }
}

void MainWindow::initializeConnections()
{
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendRequest);
    connect(httpClient, &HttpClient::finished, this, &MainWindow::processResponse);
    connect(ui->urlLineEdit, &QLineEdit::textEdited, this, &MainWindow::processParams);
}

void MainWindow::initializeHeaderTables()
{
    ui->responseHeadersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::initializeMethodComboBox()
{
    QStringList methodList = { "GET", "POST", "PUT", "PATCH", "DELETE", "HEAD", "OPTIONS" };
    ui->methodComboBox->addItems(methodList);
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
