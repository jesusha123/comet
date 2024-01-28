#ifndef METHODCOMBOBOX_H
#define METHODCOMBOBOX_H

#include <QComboBox>
#include "http_method.h"

class MethodComboBox : public QComboBox
{
    Q_OBJECT
public:
    MethodComboBox(QWidget *parent = nullptr);
signals:
    void requestBodyAllowed(Http::HasBody reqHasBody);
private:
    void processIndexChange(int index);
};

#endif // METHODCOMBOBOX_H
