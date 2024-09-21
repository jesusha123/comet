#ifndef REQUESTINFOTABLEWIDGET_H
#define REQUESTINFOTABLEWIDGET_H

#include "PropertyTableWidget.h"

class RequestInfoTableWidget : public PropertyTableWidget
{
    Q_OBJECT
public:
    explicit RequestInfoTableWidget(QWidget *parent = nullptr);
private:
    bool ignoreItemChanged;
private slots:
    void maintainBlankRowOnChange(QTableWidgetItem *item);
};

#endif // REQUESTINFOTABLEWIDGET_H
