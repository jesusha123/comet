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
    , workspace("C:/temp/comet")
{
    ui->setupUi(this);

    // Force left side to be smaller. There is probably a cleaner way...
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    // Set up collection model and view
    requestModel.setRootPath(workspace);
    requestModel.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    QStringList nameFilters;
    nameFilters << "*.yaml" << "*.yml";
    requestModel.setNameFilters(nameFilters);
    requestModel.setNameFilterDisables(false);

    // Set up collection view
    ui->collectionView->setFileSystemModel(&requestModel);
    ui->collectionView->setRootIndex(requestModel.index(workspace));
    ui->collectionView->setColumnHidden(1, true); // Hide Size
    ui->collectionView->setColumnHidden(2, true); // Hide Type
    ui->collectionView->setColumnHidden(3, true); // Hide Date Modified

    connect(ui->actionClose, &QAction::triggered, ui->tabWidget, &RequestTabWidget::closeActiveTab);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::deleteRequest);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionRename, &QAction::triggered, this, &MainWindow::renameRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &RequestTabWidget::tabChanged, ui->collectionView, &CollectionTreeView::selectFile);
    connect(ui->collectionView, &CollectionTreeView::fileClicked, this, &MainWindow::loadRequest);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

void MainWindow::loadRequest(const QString &filePath)
{
    qInfo() << "Selected file:" << filePath;
    int tabIndex = ui->tabWidget->findRequestTab(filePath);

    if(tabIndex >= 0) {
        ui->tabWidget->setCurrentIndex(tabIndex);
    } else {
        Request request;
        request.filePath = filePath;
        if (RequestStorage::loadRequest(request)) {
            auto requestWidget = new RequestWidget(ui->tabWidget);
            requestWidget->restoreRequest(request);

            QFileInfo fileInfo(request.filePath);

            ui->tabWidget->addTab(requestWidget, fileInfo.completeBaseName());
            requestWidget->setRequestFilePath(request.filePath);
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        } else {
            qWarning() << "Error loading request";
        }
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
        Request request = requestWidget->getRequest();
        if(ensureRequestHasFilePath(request)) {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), request.filePath);
            requestWidget->setRequestFilePath(request.filePath);

            if(RequestStorage::saveRequest(request)) {
                qInfo() << "Request saved successfully";
            } else {
                qWarning() << "Error saving request";
            }
        } else {
            qInfo("Save process canceled");
        }
    } else {
        qWarning("Failed cast");
    }
}

bool MainWindow::ensureRequestHasFilePath(Request& request)
{
    bool ok = true;
    if(request.filePath.isEmpty()) {
        QString text = QInputDialog::getText(
                this,
                "Request Name",
                "Enter Request Name",
                QLineEdit::Normal,
                QString(),
                &ok);
        QDir dir(workspace);
        request.filePath = dir.absoluteFilePath(text+".yaml");
    }
    return ok;
}

void MainWindow::deleteRequest()
{
    qInfo() << "Deleting request";
    QModelIndexList selectedRows = ui->collectionView->selectionModel()->selectedRows();
    for(auto index : selectedRows) {
        qInfo() << "Processing row for deletion";
        QFileInfo fileInfo = requestModel.fileInfo(index);
        if(fileInfo.isFile()) {
            QString filePath = fileInfo.absoluteFilePath();
            qInfo() << "Attempting to delete file: " << filePath;
            if(RequestStorage::deleteRequest(filePath)) {
                qInfo() << "File deleted: " << filePath;

                int tabIndex = ui->tabWidget->findRequestTab(fileInfo.absoluteFilePath());
                if(tabIndex>=0) {
                    ui->tabWidget->closeTab(tabIndex);
                }
            }
        }
    }
}

void MainWindow::renameRequest()
{
    auto list = ui->collectionView->selectionModel()->selectedRows();
    for(auto index : list) {
        QFileInfo fileInfo = requestModel.fileInfo(index);
        if(fileInfo.isFile()) {
            bool ok = true;
            QString newName = QInputDialog::getText(
                this,
                "Request Rename",
                "Enter new request name",
                QLineEdit::Normal,
                QString(),
                &ok);

            if(ok) {
                QDir dir(workspace);
                QString prevFilePath = fileInfo.absoluteFilePath();
                QString newFilePath = dir.absoluteFilePath(newName+".yaml");
                RequestStorage::renameRequest(prevFilePath, newFilePath);

                int index = ui->tabWidget->findRequestTab(prevFilePath);
                if(index>=0) {
                    QFileInfo fileInfo(newFilePath);
                    ui->tabWidget->setTabText(index, fileInfo.completeBaseName());
                    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(ui->tabWidget->widget(index));
                    requestWidget->setRequestFilePath(newFilePath);
                }
            } else {
                qInfo() << "Rename canceled";
            }
        }
    }
}

void MainWindow::showAboutDialog()
{
    ShowAboutCommand(this).execute();
}
