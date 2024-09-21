#include "RequestTabWidget.h"
#include "RequestWidget.h"
#include "RequestTabBar.h"

RequestTabWidget::RequestTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    setTabBar(new RequestTabBar(this));

    connect(this, &QTabWidget::currentChanged, this, &RequestTabWidget::onTabChanged);
    connect(this, &QTabWidget::tabCloseRequested, this, &RequestTabWidget::closeTab);
}

int RequestTabWidget::findRequestTab(const QString &filePath)
{
    for (int i = 0; i < count(); i++) {
        RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(widget(i));
        if(filePath == requestWidget->getRequestFilePath()) {
            return i;
        }
    }
    return -1;
}

void RequestTabWidget::closeTab(int tabIndex)
{
    QWidget *w = widget(tabIndex);
    if(w) {
        removeTab(tabIndex);
        delete w;
    }
}

void RequestTabWidget::onTabChanged(int tabIndex)
{
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(this->currentWidget());
    if (requestWidget) {
        emit tabChanged(requestWidget->getRequestFilePath());
    }
}
