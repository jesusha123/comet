#include "property_table_widget.h"
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
    setAlternatingRowColors(true);
}

void PropertyTableWidget::setProperty(int row, const QString& key, const QString& value)
{
    setItem(row, 0, new QTableWidgetItem(key));
    setItem(row, 1, new QTableWidgetItem(value));
}

QList<QPair<QString, QString>> PropertyTableWidget::getProperties()
{
    QList<QPair<QString, QString>> propertyList;

    for(int rowIndex = 0; rowIndex < rowCount(); rowIndex++) {
        auto keyItem = item(rowIndex, 0);

        if(keyItem) {
            auto keyText = keyItem->text();
            if(!keyText.isEmpty()) {
                // Initialize QString with empty string to avoid processing a null QString
                QString valueText("");

                auto valueItem = item(rowIndex, 1);
                if (valueItem) {
                    valueText.append(valueItem->text().toUtf8());
                }

                propertyList.append(qMakePair(keyText, valueText));
            }
        }
    }

    return propertyList;
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
