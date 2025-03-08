#include "FileSystemModel.h"

FileSystemModel::FileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
{
}

QString FileSystemModel::path() const {
    return rootPath();
}

void FileSystemModel::setPath(const QString &path) {
    if (rootPath() != path) {
        setRootPath(path);
        emit pathChanged();
    }
}

QModelIndex FileSystemModel::rootIndex() {
    return QFileSystemModel::index(path());
}

QString FileSystemModel::toPath(const QUrl &url) const {
    return url.toLocalFile();
}
