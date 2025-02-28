#include "TableModel.h"

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    return roles;
}
