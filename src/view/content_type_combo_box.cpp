#include "content_type_combo_box.h"
#include <QStringList>
#include <QStandardItemModel>

ContentTypeComboBox::ContentTypeComboBox(QWidget *parent)
    : QComboBox(parent)
{
    const QStringList contentTypes = {
        "none",
        "application/json",
        "application/x-www-form-urlencoded",
        "application/xml",
        "multipart/form-data",
        "text/html",
        "text/plain"
    };

    addItems(contentTypes);
}
