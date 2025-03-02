#include "TableModel.h"

void TableModel::appendEmptyRow() {
    int cols = columnCount();
    QList<QStandardItem*> items;
    for (int col = 0; col < cols; ++col) {
        items.append(new QStandardItem(""));
    }
    appendRow(items);
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    return roles;
}
