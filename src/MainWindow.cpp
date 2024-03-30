#include "MainWindow.h"
#include <QDateTime>
#include "HttpClient.h"
#include "ContentTypeComboBox.h"
#include "RequestWidget.h"
#include "RequestStorage.h"
#include <QMessageBox>

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

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

void MainWindow::createRequest()
{
    auto requestWidget = new RequestWidget(httpClient, ui->tabWidget);
    ui->tabWidget->addTab(requestWidget, "Untitled Request");
}

void MainWindow::saveActiveRequest()
{
    // Add new request to collection view
    int rowCount = requestModel.rowCount();
    if(requestModel.insertRow(rowCount)) {
        QModelIndex index = requestModel.index(rowCount, 0);
        requestModel.setData(index, "Titled");
    } else {
        qWarning("Row could not be added");
    }

    // Save to storage
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->currentWidget());
    if(requestWidget) {
        auto request = requestWidget->getRequest();
        RequestStorage requestStorage;
        if(!requestStorage.save(request)) {
            qWarning("Failure to save request");
        }
    } else {
        qWarning("Failed cast");
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
