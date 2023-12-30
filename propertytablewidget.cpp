#include "propertytablewidget.h"
#include <QHeaderView>
#include <QToolButton>
#include <QApplication>

PropertyTableWidget::PropertyTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setColumnCount(2);
    setRowCount(0);

    setHorizontalHeaderLabels({ "Key", "Value" });
}

void PropertyTableWidget::setProperty(int row, const QString& key, const QString& value)
{
    setItem(row, 0, new QTableWidgetItem(key));
    setItem(row, 1, new QTableWidgetItem(value));
}

void PropertyTableWidget::appendRow()
{
    setRowCount(rowCount()+1);
}

void PropertyTableWidget::removeSelectedRows()
{
    // Need to delete from the highest row number to lowest
    auto model = selectionModel();
    int removedRowCount = 0;
    if(model) {
        auto indexes = model->selectedRows();
        QVector<int> rowVector;

        for(auto index : indexes) {
            rowVector.append(index.row());
        }

        // Sort in descending order
        std::sort(rowVector.begin(), rowVector.end(), std::greater<int>());

        for(auto row : rowVector) {
            removeRow(row);
        }
        removedRowCount = rowVector.size();
    }

    if(removedRowCount==0) {
        errorMessage.showMessage("Could not delete any rows. Select at least one row for deletion.");
    }

    emit rowsRemoved();
}
