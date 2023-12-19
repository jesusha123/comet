#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    QString requestUrl = ui->urlLineEdit->text();
    qInfo("Sending request to %s", qPrintable(requestUrl));
    networkAccessManager.get(QNetworkRequest(QUrl(requestUrl)));
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
    QStringList urlList = { "https://wikipedia.org" };
    ui->requestListWidget->addItems(urlList);
}

void MainWindow::initializeHeaderTables()
{
    ui->requestHeadersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->responseHeadersTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
