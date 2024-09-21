#include "RequestTabBar.h"
#include <QMouseEvent>

RequestTabBar::RequestTabBar(QWidget *parent)
    : QTabBar(parent)
{
}

void RequestTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        int tabIndex = tabAt(event->pos());
        if (tabIndex != -1) {
            emit tabCloseRequested(tabIndex);
        }
    }
    QTabBar::mouseReleaseEvent(event);
}
