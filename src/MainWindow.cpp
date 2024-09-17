#include "MainWindow.h"
#include <QDateTime>
#include "RequestWidget.h"
#include "RequestStorage.h"
#include "ShowAboutCommand.h"
#include <QInputDialog>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->collectionView->setModel(&requestModel);

    // Force left side to be smaller. There is probably a cleaner way...
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeActiveTab);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::deleteRequest);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionRename, &QAction::triggered, this, &MainWindow::renameRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);
    connect(ui->collectionView, &QAbstractItemView::clicked, this, &MainWindow::collectionItemActivated);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

void MainWindow::activateWorkspace(QString workspace)
{
    this->workspacePath = workspace;
    loadCollection();
}

void MainWindow::tabChanged(int tabIndex)
{
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->currentWidget());
    if(requestWidget) {
        int viewIndex = findCollectionRequest(requestWidget->getName());
        if (viewIndex >= 0) {
            auto modelIndex = requestModel.index(viewIndex);
            ui->collectionView->setCurrentIndex(modelIndex);
        }
    }
}

void MainWindow::collectionItemActivated(const QModelIndex &index)
{
    auto request = collection.at(index.row());
    int tabIndex = findRequestTab(request.name);
    if(tabIndex >= 0) {
        ui->tabWidget->setCurrentIndex(tabIndex);
    } else {
        auto requestWidget = new RequestWidget(ui->tabWidget);
        requestWidget->restoreRequest(request);

        ui->tabWidget->addTab(requestWidget, request.name);
        requestWidget->setName(request.name);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }
}

void MainWindow::loadCollection()
{
    collection = RequestStorage().readCollection(this->workspacePath);

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
    auto requestWidget = new RequestWidget(ui->tabWidget);
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
                int collectionIndex = findCollectionRequest(name);
                if(collectionIndex>=0) {
                    collection.replace(collectionIndex, request);
                } else {
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
    // Delete from: 1. File, 2. Tabs, 3. requestModel, 4. collection
    auto list = ui->collectionView->selectionModel()->selectedRows();
    for(auto index : list) {
        int row = index.row();
        if(RequestStorage().deleteRequest(collection.at(row))) { // 1. File
            QString name = requestModel.stringList().at(row);
            int tabIndex = findRequestTab(name);
            if(tabIndex >= 0) {
                closeTab(tabIndex); // 2. Tabs
            }
            requestModel.removeRows(row, 1); // 3. requestModel
            collection.remove(row); // 4. collection
        }
    }
}

void MainWindow::renameRequest()
{
    // Rename here: 1. File, 2. Tab title, 3. RequestWidget, 4. requestModel, 5. collection
    auto list = ui->collectionView->selectionModel()->selectedRows();
    for(auto index : list) {
        int row = index.row();
        bool ok = true;
        QString newName = QInputDialog::getText(
                this,
                "Request Rename",
                "Enter new request name",
                QLineEdit::Normal,
                QString(),
                &ok);
        if(ok && RequestStorage().renameRequest(collection.at(row), newName)) {
            QString name = requestModel.stringList().at(row);
            int tabIndex = findRequestTab(name);
            if(tabIndex >= 0) {
                ui->tabWidget->tabBar()->setTabText(tabIndex, newName); // 2. Tab title
                RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->currentWidget());
                requestWidget->setName(newName); // RequestWidget
            }
            QModelIndex index = requestModel.index(row, 0);
            requestModel.setData(index, newName); // 4. requestModel
            collection[row].name = newName; // 5. collection
        } else {
            qWarning("Failure to rename file");
        }
    }
}

void MainWindow::showAboutDialog()
{
    ShowAboutCommand(this).execute();
}
