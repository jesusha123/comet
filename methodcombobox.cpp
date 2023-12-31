#include "methodcombobox.h"
#include "httpmethod.h"

MethodComboBox::MethodComboBox(QWidget *parent)
    : QComboBox(parent)
{
    addItems(Http::OfficialMethods);
}
