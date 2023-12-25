#ifndef PROPERTYTABLEWIDGET_H
#define PROPERTYTABLEWIDGET_H

#include <QTableWidget>

class PropertyTableWidget : public QTableWidget
{
public:
    PropertyTableWidget();

private slots:
    void ensureEmptyBottomRow(QTableWidgetItem *item);
    void deleteButtonClicked();

private:
    void addRow(int row);
};

#endif // PROPERTYTABLEWIDGET_H
