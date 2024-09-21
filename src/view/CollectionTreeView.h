#ifndef COLLECTIONTREEVIEW_H
#define COLLECTIONTREEVIEW_H

#include <QTreeView>

class QFileSystemModel;

class CollectionTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CollectionTreeView(QWidget *parent = nullptr);

    void setFileSystemModel(QFileSystemModel* model);

public slots:
    void selectFile(const QString &filePath);

signals:
    void fileClicked(const QString &absoluteFilePath);

private:
    QFileSystemModel* fileSystemModel;

private slots:
    void onItemClicked(const QModelIndex &index);
};

#endif // COLLECTIONTREEVIEW_H
