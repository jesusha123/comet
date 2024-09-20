#ifndef REQUESTTABBAR_H
#define REQUESTTABBAR_H

#include <QTabBar>

class RequestTabBar : public QTabBar
{
public:
    explicit RequestTabBar(QWidget *parent = nullptr);
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // REQUESTTABBAR_H
