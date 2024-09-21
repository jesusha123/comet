#include "CreateRequestCommand.h"
#include "DeleteRequestCommand.h"
#include "LoadRequestCommand.h"
#include "MainWindow.h"
#include <QAbstractItemView>
#include <QDateTime>
#include <QInputDialog>
#include "RenameRequestCommand.h"
#include "SaveRequestCommand.h"
#include "ShowAboutCommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workspace("C:/temp/comet")
{
    ui->setupUi(this);

    // Force left side to be smaller. There is probably a cleaner way...
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    // Set up collection view
    ui->collectionView->loadWorkspace(workspace);

    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::deleteRequest);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionRename, &QAction::triggered, this, &MainWindow::renameRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &RequestTabWidget::tabChanged, ui->collectionView, &CollectionTreeView::selectFile);
    connect(ui->collectionView, &CollectionTreeView::fileClicked, this, &MainWindow::loadRequest);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

QString MainWindow::getWorkspace()
{
    return workspace;
}

void MainWindow::loadRequest(const QString &filePath)
{
    LoadRequestCommand(filePath, ui->tabWidget).execute();
}

void MainWindow::createRequest()
{
    CreateRequestCommand(ui->tabWidget).execute();
}

void MainWindow::saveActiveRequest()
{
    SaveRequestCommand(this, ui->tabWidget).execute();
}

void MainWindow::deleteRequest()
{
    DeleteRequestCommand(ui->collectionView, ui->tabWidget).execute();
}

void MainWindow::renameRequest()
{
    RenameRequestCommand(this, ui->collectionView, ui->tabWidget).execute();
}

void MainWindow::showAboutDialog()
{
    ShowAboutCommand(this).execute();
}
