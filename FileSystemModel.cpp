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

        // Wait to install name filters, otherwise rootPath defaults to system root.
        setNameFilters(QStringList() << "*.cmt");
        setNameFilterDisables(false);

        emit pathChanged();
    }
}

QModelIndex FileSystemModel::rootIndex() {
    return QFileSystemModel::index(path());
}

QString FileSystemModel::toPath(const QUrl &url) const {
    return url.toLocalFile();
}

QString FileSystemModel::filePathForIndex(const QModelIndex &index) const {
    return QFileSystemModel::filePath(index);
}

QHash<int, QByteArray> FileSystemModel::roleNames() const {
    QHash<int, QByteArray> roles = QFileSystemModel::roleNames();
    roles[FilePathRole] = "filePath";
    roles[IsDirRole] = "isDir";
    return roles;
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const {
    if (role == FilePathRole) {
        return filePath(index);
    } else if (role == IsDirRole) {
        return QFileSystemModel::isDir(index);
    }
    return QFileSystemModel::data(index, role);
}
