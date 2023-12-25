#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 5);

    initializeConnections();
    initializeCollection();
    initializeHeaderTables();
    initializeVerbComboBox();

    ui->statusBar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    const QString requestUrl = ui->urlLineEdit->text();
    const QString bodyText = ui->requestBodyPlainTextEdit->toPlainText();
    const QString verb = ui->verbComboBox->currentText();

    QNetworkRequest networkRequest = QNetworkRequest(QUrl(requestUrl));
    addRequestHeaders(&networkRequest);

    qInfo("Sending request to %s", qPrintable(requestUrl));
    networkAccessManager.sendCustomRequest(networkRequest, verb.toUtf8(), bodyText.toUtf8());
}

void MainWindow::processReply(QNetworkReply *reply)
{
    qInfo("Reply finished from %s", qPrintable(reply->request().url().toString()));

    QByteArray data = reply->readAll();
    ui->responseBodyPlainTextEdit->setPlainText(data);

    QTableWidget *tableWidget = ui->responseHeadersTableWidget;
    const QList<QNetworkReply::RawHeaderPair>& headerPairs = reply->rawHeaderPairs();
    tableWidget->clearContents();
    tableWidget->setRowCount(headerPairs.count());

    for(int rowIndex=0; rowIndex<headerPairs.count(); rowIndex++) {
        const QNetworkReply::RawHeaderPair &headerPair = headerPairs.at(rowIndex);
        qInfo("Header: \"%s\": \"%s\"", qPrintable(headerPair.first), qPrintable(headerPair.second));
        tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(headerPair.first));
        tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(headerPair.second));
    }

    auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()) {
        ui->statusBar->showMessage(QString("Status: %1").arg(statusCode.toString()));
    } else {
        ui->statusBar->showMessage(QString("Error: %1").arg(reply->errorString()));
    }
}

void MainWindow::changeActiveRequest(QListWidgetItem *item)
{
    QString itemText = item->text();
    qInfo("Changing active request to %s", qPrintable(itemText));
    ui->urlLineEdit->setText(itemText);
}


void MainWindow::initializeConnections()
{
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendRequest);
    connect(&networkAccessManager, &QNetworkAccessManager::finished, this, &MainWindow::processReply);
    connect(ui->requestListWidget, &QListWidget::itemClicked, this, &MainWindow::changeActiveRequest);
}

void MainWindow::initializeCollection()
{
    QStringList urlList = { "http://localhost:3000" };
    ui->requestListWidget->addItems(urlList);
}

void MainWindow::initializeHeaderTables()
{
    ui->responseHeadersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::initializeVerbComboBox()
{
    QStringList methodList = { "GET", "POST", "PUT", "PATCH", "DELETE", "HEAD", "OPTIONS" };
    ui->verbComboBox->addItems(methodList);
}

void MainWindow::addRequestHeaders(QNetworkRequest* networkRequest)
{
    for(int rowIndex=0; rowIndex<ui->requestHeadersTableWidget->rowCount(); rowIndex++) {
        auto keyItem = ui->requestHeadersTableWidget->item(rowIndex, 0);

        if(keyItem) {
            auto keyText = keyItem->text();
            if(!keyText.isEmpty()) {
                // Initialize QByteArray with empty string to avoid it being treated as null
                QByteArray valueText("");

                auto valueItem = ui->requestHeadersTableWidget->item(rowIndex, 1);
                if (valueItem) {
                    valueText.append(valueItem->text().toUtf8());
                }

                networkRequest->setRawHeader(keyText.toUtf8(), valueText);
            }
        }
    }
}
