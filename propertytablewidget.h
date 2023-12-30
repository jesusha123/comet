#ifndef PROPERTYTABLEWIDGET_H
#define PROPERTYTABLEWIDGET_H

#include <QTableWidget>
#include <QErrorMessage>

class PropertyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    PropertyTableWidget(QWidget *parent = nullptr);
    void setProperty(int row, const QString& key, const QString& value);
public slots:
    void appendRow();
    void removeSelectedRows();
signals:
    void rowsRemoved();
private:
    QErrorMessage errorMessage;
};

#endif // PROPERTYTABLEWIDGET_H
