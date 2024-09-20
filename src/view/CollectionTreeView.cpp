#include "CollectionTreeView.h"
#include <QFileSystemModel>

CollectionTreeView::CollectionTreeView(QWidget *parent)
    : QTreeView(parent)
{
    connect(this, &QTreeView::clicked, this, &CollectionTreeView::onItemClicked);
}

void CollectionTreeView::selectFile(const QString &filePath)
{
    QModelIndex index = fileSystemModel->index(filePath);
    if (index.isValid()) {
        setCurrentIndex(index);
    }
}

void CollectionTreeView::setFileSystemModel(QFileSystemModel* fileSystemModel)
{
    setModel(fileSystemModel);
    this->fileSystemModel = fileSystemModel;
}

void CollectionTreeView::onItemClicked(const QModelIndex &index)
{
    qInfo() << "Item clicked";
    QFileInfo fileInfo = fileSystemModel->fileInfo(index);

    if (fileInfo.isFile()) {
        QString absoluteFilePath = fileInfo.absoluteFilePath();
        emit fileClicked(absoluteFilePath);
    }
}
