#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_main_window.h"

class HttpClient;
class RequestWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void loadFolder();
    QString getFolder();

private slots:
    void selectFolder();
    void loadRequest(const QString &filePath);
    void createRequest();
    void deleteRequest();
    void renameRequest();
    void saveActiveRequest();
    void showAboutDialog();

private:
    void setFolder(const QString& folder);

    std::unique_ptr<Ui::MainWindow> ui;
    QString folder;
};

#endif
