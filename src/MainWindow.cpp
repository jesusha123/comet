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

    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeTab);
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
    auto requestWidget = new RequestWidget(httpClient, ui->tabWidget);
    requestWidget->restoreRequest(request);

    ui->tabWidget->addTab(requestWidget, request.name);
    requestWidget->setName(request.name);
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
}

void MainWindow::saveActiveRequest()
{
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->currentWidget());
    if(requestWidget) {
        auto request = requestWidget->getRequest();
        ensureRequestHasName(request);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), request.name);
        requestWidget->setName(request.name);

        RequestStorage requestStorage;
        QString name = requestWidget->getName();
        if(requestStorage.saveRequest(request, name)) {
            addRequestToCollection(request);
            qInfo("Saved request with id %s", qPrintable(name));
        } else {
            qWarning("Failure to save request");
        }
    } else {
        qWarning("Failed cast");
    }
}

void MainWindow::ensureRequestHasName(Request& request)
{
    if(request.name.isEmpty()) {
        QString text = QInputDialog::getText(this, "Request Name", "Request Name");
        qInfo("Request name is: %s", qPrintable(text));
        request.name = text;
    }
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
