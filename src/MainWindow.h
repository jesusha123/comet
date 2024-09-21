#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include "ui_main_window.h"
#include "Request.h"

class HttpClient;
class RequestWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void loadRequest(const QString &filePath);
    void createRequest();
    void deleteRequest();
    void renameRequest();
    void saveActiveRequest();
    void showAboutDialog();

private:
    bool ensureRequestHasFilePath(Request& request);

    std::unique_ptr<Ui::MainWindow> ui;
    QString workspace;
    QFileSystemModel requestModel;
};

#endif
