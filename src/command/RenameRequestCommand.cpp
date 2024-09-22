#include "CollectionTreeView.h"
#include "MainWindow.h"
#include <QInputDialog>
#include "RenameRequestCommand.h"
#include "RequestStorage.h"
#include "RequestWidget.h"

RenameRequestCommand::RenameRequestCommand(
    MainWindow *mainWindow,
    CollectionTreeView *collectionTreeView,
    RequestTabWidget* requestTabWidget)
    : mainWindow(mainWindow)
    , collectionTreeView(collectionTreeView)
    , requestTabWidget(requestTabWidget)
{
}

void RenameRequestCommand::execute()
{
    auto list = collectionTreeView->selectionModel()->selectedRows();
    for(auto index : list) {
        QFileInfo fileInfo = collectionTreeView->getFileSystemModel()->fileInfo(index);
        if(fileInfo.isFile()) {
            bool ok = true;
            QString newName = QInputDialog::getText(
                mainWindow,
                "Request Rename",
                "Enter new request name",
                QLineEdit::Normal,
                QString(),
                &ok);

            if(ok) {
                QDir dir(mainWindow->getFolder());
                QString prevFilePath = fileInfo.absoluteFilePath();
                QString newFilePath = dir.absoluteFilePath(newName+".yaml");
                RequestStorage::renameRequest(prevFilePath, newFilePath);

                int index = requestTabWidget->findRequestTab(prevFilePath);
                if(index>=0) {
                    QFileInfo fileInfo(newFilePath);
                    requestTabWidget->setTabText(index, fileInfo.completeBaseName());
                    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(requestTabWidget->widget(index));
                    requestWidget->setRequestFilePath(newFilePath);
                }
            } else {
                qInfo() << "Rename canceled";
            }
        }
    }
}
