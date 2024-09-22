#include "CreateRequestCommand.h"
#include "DeleteRequestCommand.h"
#include "LoadRequestCommand.h"
#include "MainWindow.h"
#include <QAbstractItemView>
#include <QDateTime>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include "RenameRequestCommand.h"
#include "SaveRequestCommand.h"
#include "ShowAboutCommand.h"

const QString LastFolderSettingsKey = QStringLiteral("lastFolder");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Force left side to be smaller. There is probably a cleaner way...
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::deleteRequest);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::createRequest);
    connect(ui->actionRename, &QAction::triggered, this, &MainWindow::renameRequest);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveActiveRequest);
    connect(ui->tabWidget, &RequestTabWidget::tabChanged, ui->collectionView, &CollectionTreeView::selectFile);
    connect(ui->collectionView, &CollectionTreeView::fileClicked, this, &MainWindow::loadRequest);
    connect(ui->actionOpenFolder, &QAction::triggered, this, &MainWindow::selectFolder);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
}

void MainWindow::loadFolder()
{
    QSettings settings;
    QString folder = settings.value(LastFolderSettingsKey, "").toString();

    if (!folder.isEmpty() && QDir(folder).exists()) {
        setFolder(folder);
    } else {
        QMessageBox::information(this,
                                 "Select Folder",
                                 "Please select a folder to store requests.");
        selectFolder();
    }
}

void MainWindow::selectFolder()
{
    QString newFolder = QFileDialog::getExistingDirectory(
        this,
        "Select Folder",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly);

    if (!newFolder.isEmpty()) {
        setFolder(newFolder);
        QSettings settings;
        settings.setValue(LastFolderSettingsKey, newFolder);
    } else if (folder.isEmpty()) {
        QMessageBox::warning(
            this,
            "Folder Required",
            "A folder is required to proceed. No folder was selected. Exiting application.");
        QTimer::singleShot(0, this, &QCoreApplication::quit);
    }
}

QString MainWindow::getFolder()
{
    return folder;
}

void MainWindow::setFolder(const QString& folder)
{
    qInfo() << "Setting folder: " << folder;
    this->folder = folder;
    this->setWindowTitle("Comet - " + folder);
    ui->collectionView->loadFolder(folder);
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
