#include <QPushButton>
#include "RequestInfoTableWidget.h"

RequestInfoTableWidget::RequestInfoTableWidget(QWidget *parent)
    : PropertyTableWidget(parent)
    , ignoreItemChanged(false)
{
    setColumnCount(3);
    setHorizontalHeaderLabels({ "Key", "Value", "" });

    connect(this, &QTableWidget::itemChanged, this, &RequestInfoTableWidget::maintainBlankRowOnChange);
    connect(model(), &QAbstractItemModel::rowsInserted, this, &RequestInfoTableWidget::onRowsInserted);

    insertRow(0); // Call after setting onRowsInserted connection, so we add a delete button.
}

void RequestInfoTableWidget::addDeleteButtonToRow(int row)
{
    QPushButton *deleteButton = new QPushButton();
    deleteButton->setIcon(QIcon::fromTheme("user-trash"));
    deleteButton->setFlat(true);

    connect(deleteButton, &QPushButton::clicked, this, &RequestInfoTableWidget::onDeleteButtonClicked);

    setCellWidget(row, 2, deleteButton);
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

void RequestInfoTableWidget::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    for (int row = first; row <= last; ++row)
    {
        addDeleteButtonToRow(row);
    }
}

void RequestInfoTableWidget::onDeleteButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button)
    {
        int rowToDelete = -1;
        for (int row = 0; row < rowCount(); ++row)
        {
            if (cellWidget(row, 2) == button)
            {
                rowToDelete = row;
                break;
            }
        }

        // Remove row only if we found a match, and if it's not the last row
        if (rowToDelete != -1 && rowToDelete != rowCount()-1)
        {
            removeRow(rowToDelete);
        }
    }
}
