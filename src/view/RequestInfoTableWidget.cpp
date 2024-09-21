#include "RequestInfoTableWidget.h"

RequestInfoTableWidget::RequestInfoTableWidget(QWidget *parent)
    : PropertyTableWidget(parent)
    , ignoreItemChanged(false)
{
    insertRow(0);

    connect(this, &QTableWidget::itemChanged, this, &RequestInfoTableWidget::maintainBlankRowOnChange);
}

void RequestInfoTableWidget::maintainBlankRowOnChange(QTableWidgetItem *item)
{
    if (!ignoreItemChanged) {
        int row = item->row();

        if (row == rowCount() - 1 && !item->text().isEmpty())
        {
            ignoreItemChanged = true;
            insertRow(rowCount());
            ignoreItemChanged = false;
        }
    }
}
