#ifndef COLLECTIONTREEVIEW_H
#define COLLECTIONTREEVIEW_H

#include "FileSystemModel.h"
#include <QTreeView>

class CollectionTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CollectionTreeView(QWidget *parent = nullptr);

    void loadWorkspace(const QString& workspacePath);
    FileSystemModel* getFileSystemModel();

public slots:
    void selectFile(const QString &filePath);

signals:
    void fileClicked(const QString &absoluteFilePath);

private:
    FileSystemModel fileSystemModel;

private slots:
    void onItemClicked(const QModelIndex &index);
};

#endif // COLLECTIONTREEVIEW_H
