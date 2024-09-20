#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
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
    void collectionItemActivated(const QModelIndex& index);

private:
    bool ensureRequestHasFilePath(Request& request);
    int findRequestTab(QString name);

    std::unique_ptr<Ui::MainWindow> ui;
    QString workspace;
    QFileSystemModel requestModel;
};

#endif
