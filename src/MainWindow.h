#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "ui_main_window.h"

class HttpClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void createRequest();
    void closeTab(int index);
    void showAboutDialog();
    void saveActiveRequest();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<HttpClient> httpClient;
    QStringListModel requestModel;
};

#endif
