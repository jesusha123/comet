#ifndef METHODCOMBOBOX_H
#define METHODCOMBOBOX_H

#include <QComboBox>

class MethodComboBox : public QComboBox
{
    Q_OBJECT
public:
    MethodComboBox(QWidget *parent = nullptr);
signals:
    void requestBodyAllowed(bool activeMethodAllowsBody);
private:
    void processIndexChange(int index);
};

#endif // METHODCOMBOBOX_H
