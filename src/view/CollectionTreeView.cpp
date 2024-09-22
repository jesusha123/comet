#include "CollectionTreeView.h"

CollectionTreeView::CollectionTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setModel(&fileSystemModel);
    connect(this, &QTreeView::clicked, this, &CollectionTreeView::onItemClicked);
}

void CollectionTreeView::loadFolder(const QString& folderPath)
{
    fileSystemModel.setRootPath(folderPath);
    setRootIndex(fileSystemModel.index(folderPath));
    setColumnHidden(1, true); // Hide Size
    setColumnHidden(2, true); // Hide Type
    setColumnHidden(3, true); // Hide Date Modified
}

void CollectionTreeView::selectFile(const QString &filePath)
{
    QModelIndex index = fileSystemModel.index(filePath);
    if (index.isValid()) {
        setCurrentIndex(index);
    }
}

FileSystemModel* CollectionTreeView::getFileSystemModel()
{
    return &fileSystemModel;
}

void CollectionTreeView::onItemClicked(const QModelIndex &index)
{
    qInfo() << "Item clicked";
    QFileInfo fileInfo = fileSystemModel.fileInfo(index);

    if (fileInfo.isFile()) {
        QString absoluteFilePath = fileInfo.absoluteFilePath();
        emit fileClicked(absoluteFilePath);
    }
}
