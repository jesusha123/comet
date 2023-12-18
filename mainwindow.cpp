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

    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendRequest);
    connect(&networkAccessManager, &QNetworkAccessManager::finished, this, &MainWindow::processReply);
    connect(ui->requestListWidget, &QListWidget::itemClicked, this, &MainWindow::changeActiveRequest);

    initializeCollection();
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
    ui->responseWebEngine->setHtml(data);
}

void MainWindow::changeActiveRequest(QListWidgetItem *item)
{
    QString itemText = item->text();
    qInfo("Changing active request to %s", qPrintable(itemText));
    ui->urlLineEdit->setText(itemText);
}

void MainWindow::initializeCollection()
{
    QFile collectionFile("/Users/max/temp/mycollection.json");
    if (!collectionFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }
    QByteArray collectionData = collectionFile.readAll();
    QJsonDocument collectionDocument(QJsonDocument::fromJson(collectionData));
    QJsonObject collectionObject = collectionDocument.object();
    QJsonArray requestsArray = collectionObject["requests"].toArray();
    for (const QJsonValue &requestValue : requestsArray) {
        QString name = requestValue.toObject()["name"].toString();
        QString url = requestValue.toObject()["url"].toString();
        qInfo("Loading request from collection: \"%s\" [%s]", qPrintable(name), qPrintable(url));
        ui->requestListWidget->addItem(url);
    }
}
