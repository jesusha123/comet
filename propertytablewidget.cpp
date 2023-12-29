#include "propertytablewidget.h"
#include <QHeaderView>
#include <QToolButton>
#include <QApplication>

PropertyTableWidget::PropertyTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::AllEditTriggers);

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
