#include "MainWindow.h"
#include <QDateTime>
#include "HttpClient.h"
#include "ContentTypeComboBox.h"
#include "RequestWidget.h"
#include "RequestStorage.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , httpClient(new HttpClient)
{
    ui->setupUi(this);
    ui->collectionView->setModel(&requestModel);

    // Force left side to be smaller. There is probably a cleaner way...
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeActiveTab);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::deleteRequest);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->collectionView, &QAbstractItemView::clicked, this, &MainWindow::collectionItemActivated);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);

    loadCollection();
}

void MainWindow::collectionItemActivated(const QModelIndex &index)
{
    auto request = collection.at(index.row());
    int tabIndex = findRequestTab(request.name);
    if(tabIndex >= 0) {
        ui->tabWidget->setCurrentIndex(tabIndex);
    } else {
        auto requestWidget = new RequestWidget(httpClient, ui->tabWidget);
        requestWidget->restoreRequest(request);

        ui->tabWidget->addTab(requestWidget, request.name);
        requestWidget->setName(request.name);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
}

void MainWindow::loadCollection()
{
    collection = RequestStorage().readCollection();

    for(auto request : collection) {
        addRequestToModel(request);
    }
}

void MainWindow::addRequestToCollection(Request &request)
{
    qInfo("addRequestToCollection: %s", qPrintable(request.name));
    collection.append(request);
    addRequestToModel(request);
}

void MainWindow::addRequestToModel(Request& request)
{
    int rowCount = requestModel.rowCount();
    if(requestModel.insertRow(rowCount)) {
        QModelIndex index = requestModel.index(rowCount, 0);
        requestModel.setData(index, request.name);
    } else {
        qWarning("Request could not be added to request model");
    }
}

void MainWindow::createRequest()
{
    auto requestWidget = new RequestWidget(httpClient, ui->tabWidget);
    ui->tabWidget->addTab(requestWidget, "Untitled Request");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::saveActiveRequest()
{
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->currentWidget());
    if(requestWidget) {
        auto request = requestWidget->getRequest();
        if(ensureRequestHasName(request)) {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), request.name);
            requestWidget->setName(request.name);

            RequestStorage requestStorage;
            QString name = requestWidget->getName();
            if(requestStorage.saveRequest(request, name)) {
                if(!requestExists(name)) {
                    addRequestToCollection(request);
                }
                qInfo("Saved request with id %s", qPrintable(name));
            } else {
                qWarning("Failure to save request");
            }
        } else {
            qInfo("Save process canceled");
        }
    } else {
        qWarning("Failed cast");
    }
}

bool MainWindow::requestExists(QString name)
{
    return findCollectionRequest(name)>=0;
}

int MainWindow::findCollectionRequest(QString name)
{
    for(int i=0; i<requestModel.stringList().count(); i++) {
        if(name == requestModel.stringList().at(i)) {
            return i;
        }
    }
    return -1;
}

int MainWindow::findRequestTab(QString name)
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->widget(i));
        if(name == requestWidget->getName()) {
            return i;
        }
    }
    return -1;
}

bool MainWindow::ensureRequestHasName(Request& request)
{
    bool ok = true;
    if(request.name.isEmpty()) {
        QString text = QInputDialog::getText(
                this,
                "Request Name",
                "Enter Request Name",
                QLineEdit::Normal,
                QString(),
                &ok);
        request.name = text;
    }
    return ok;
}

void MainWindow::closeActiveTab()
{
    auto index = ui->tabWidget->currentIndex();
    if(index >= 0) {
        closeTab(index);
    }
}

void MainWindow::closeTab(int index)
{
    auto widget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete widget;
}

void MainWindow::deleteRequest()
{
    // Delete from: 1. File, 1. Tabs, 2. requestModel, 3. collection
    auto list = ui->collectionView->selectionModel()->selectedRows();
    for(auto index : list) {
        int row = index.row();
        if(RequestStorage().deleteRequest(collection.at(row))) {
            QString name = requestModel.stringList().at(row);
            int tabIndex = findRequestTab(name);
            if(tabIndex >= 0) {
                closeTab(tabIndex);
            }
            requestModel.removeRows(row, 1);
            collection.remove(row);
        }
    }
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
