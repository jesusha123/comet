#ifndef REQUESTTABWIDGET_H
#define REQUESTTABWIDGET_H

#include <QTabWidget>

class RequestTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit RequestTabWidget(QWidget *parent = nullptr);

    int findRequestTab(const QString &filePath);

signals:
    void tabChanged(const QString &filePath);

public slots:
    void closeActiveTab();
    void closeTab(int tabIndex);

private slots:
    void onTabChanged(int tabIndex);
};

#endif // REQUESTTABWIDGET_H
