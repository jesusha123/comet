#include "PropertyTableWidget.h"
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
