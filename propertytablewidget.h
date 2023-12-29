#ifndef PROPERTYTABLEWIDGET_H
#define PROPERTYTABLEWIDGET_H

#include <QTableWidget>

class PropertyTableWidget : public QTableWidget
{
public:
    PropertyTableWidget(QWidget *parent = nullptr);
    void setProperty(int row, const QString& key, const QString& value);
public slots:
    void appendRow();
};

#endif // PROPERTYTABLEWIDGET_H
