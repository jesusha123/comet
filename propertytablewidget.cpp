#include "propertytablewidget.h"
#include <QHeaderView>
#include <QToolButton>
#include <QApplication>

PropertyTableWidget::PropertyTableWidget()
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::AllEditTriggers);

    setColumnCount(3);
    setRowCount(0);

    setHorizontalHeaderLabels({ "Key", "Value", "Del" });

    connect(this, &PropertyTableWidget::itemChanged, this, &PropertyTableWidget::ensureEmptyBottomRow);

    addRow(0);
}

void PropertyTableWidget::ensureEmptyBottomRow(QTableWidgetItem *item)
{
    if((item->row()+1)==rowCount() && !item->text().isEmpty()) {
        addRow(rowCount());
    }
}

void PropertyTableWidget::deleteButtonClicked()
{
    QWidget* deleteButton = qobject_cast<QWidget*>(sender());
    if(deleteButton) {
        int row = indexAt(deleteButton->pos()).row();
        if(rowCount()>1 && (rowCount()-1) != row) {
            removeRow(row);
        }
    }
}

void PropertyTableWidget::addRow(int row)
{
    insertRow(row);

    QToolButton* deleteButton = new QToolButton;
    QIcon trashIcon = QApplication::style()->standardIcon(QStyle::SP_TrashIcon);
    deleteButton->setIcon(trashIcon);
    setCellWidget(row, 2, deleteButton);
    connect(deleteButton, &QToolButton::clicked, this, &PropertyTableWidget::deleteButtonClicked);
}
