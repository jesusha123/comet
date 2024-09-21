#include "CollectionTreeView.h"
#include "DeleteRequestCommand.h"
#include "RequestStorage.h"
#include "RequestTabWidget.h"
#include <QFileInfo>
#include <QFileSystemModel>

DeleteRequestCommand::DeleteRequestCommand(CollectionTreeView *collectionTreeView, RequestTabWidget *requestTabWidget)
    : collectionTreeView(collectionTreeView)
    , requestTabWidget(requestTabWidget)
{
}

void DeleteRequestCommand::execute()
{
    qInfo() << "Deleting request";
    QModelIndexList selectedRows = collectionTreeView->selectionModel()->selectedRows();
    for(auto index : selectedRows) {
        qInfo() << "Processing row for deletion";
        QFileInfo fileInfo = collectionTreeView->getFileSystemModel()->fileInfo(index);
        if(fileInfo.isFile()) {
            QString filePath = fileInfo.absoluteFilePath();
            qInfo() << "Attempting to delete file: " << filePath;
            if(RequestStorage::deleteRequest(filePath)) {
                qInfo() << "File deleted: " << filePath;

                int tabIndex = requestTabWidget->findRequestTab(fileInfo.absoluteFilePath());
                if(tabIndex>=0) {
                    requestTabWidget->closeTab(tabIndex);
                }
            }
        }
    }
}
