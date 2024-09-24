#ifndef REQUESTINFOTABLEWIDGET_H
#define REQUESTINFOTABLEWIDGET_H

#include "PropertyTableWidget.h"

class RequestInfoTableWidget : public PropertyTableWidget
{
    Q_OBJECT
public:
    explicit RequestInfoTableWidget(QWidget *parent = nullptr);
private:
    void addDeleteButtonToRow(int row);
    bool ignoreItemChanged;
private slots:
    void maintainBlankRowOnChange(QTableWidgetItem *item);
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onDeleteButtonClicked();
};

#endif // REQUESTINFOTABLEWIDGET_H
