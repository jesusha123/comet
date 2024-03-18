#include "MethodComboBox.h"
#include "HttpMethod.h"

MethodComboBox::MethodComboBox(QWidget *parent)
    : QComboBox(parent)
{
    addItems(Http::OfficialMethods);

    connect(this, &QComboBox::currentIndexChanged, this, &MethodComboBox::processIndexChange);
}

void MethodComboBox::processIndexChange(int index)
{
    auto hasRequestBody = Http::hasRequestBody(static_cast<Http::Method>(index));
    emit requestBodyAllowed(hasRequestBody);
}
