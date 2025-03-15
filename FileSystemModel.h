#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QtQml/qqmlregistration.h>
#include <QUrl>

class FileSystemModel : public QFileSystemModel {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    explicit FileSystemModel(QObject *parent = nullptr);

    QString path() const;
    void setPath(const QString &path);

    Q_INVOKABLE QModelIndex rootIndex();
    Q_INVOKABLE QString toPath(const QUrl &url) const;
    Q_INVOKABLE QString filePathForIndex(const QModelIndex &index) const;
signals:
    void pathChanged();
protected:
    enum Roles {
        FilePathRole = Qt::UserRole + 1,
        IsDirRole = Qt::UserRole + 2
    };

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif
