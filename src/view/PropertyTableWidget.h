#ifndef PROPERTYTABLEWIDGET_H
#define PROPERTYTABLEWIDGET_H

#include <QTableWidget>

class PropertyTableWidget : public QTableWidget
{
public:
    explicit PropertyTableWidget(QWidget *parent = nullptr);
    void setProperty(int row, const QString& key, const QString& value);
    QList<QPair<QString, QString>> getProperties();
};

#endif // PROPERTYTABLEWIDGET_H
