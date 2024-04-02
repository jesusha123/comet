#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "ui_main_window.h"
#include "Request.h"

class HttpClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void createRequest();
    void deleteRequest();
    void renameRequest();
    void closeActiveTab();
    void closeTab(int index);
    void tabChanged(int tabIndex);
    void showAboutDialog();
    void saveActiveRequest();
    void addRequestToCollection(Request& request);
    void addRequestToModel(Request& request);
    void collectionItemActivated(const QModelIndex& index);

private:
    void loadCollection();
    bool ensureRequestHasName(Request& request);
    bool requestExists(QString name);
    int findCollectionRequest(QString name);
    int findRequestTab(QString name);

    std::unique_ptr<Ui::MainWindow> ui;
    QStringListModel requestModel;
    QList<Request> collection;
};

#endif
