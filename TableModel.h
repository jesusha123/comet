#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QStandardItemModel>

class TableModel : public QStandardItemModel {
    Q_OBJECT
public:
    using QStandardItemModel::QStandardItemModel;

    Q_INVOKABLE void appendEmptyRow();
    QHash<int, QByteArray> roleNames() const override;
};

#endif
