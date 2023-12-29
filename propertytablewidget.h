#ifndef PROPERTYTABLEWIDGET_H
#define PROPERTYTABLEWIDGET_H

#include <QTableWidget>

class PropertyTableWidget : public QTableWidget
{
public:
    PropertyTableWidget();
    void setProperty(int row, const QString& key, const QString& value);
};

#endif // PROPERTYTABLEWIDGET_H
