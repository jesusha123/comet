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

    QString getWorkspace();

private slots:
    void loadRequest(const QString &filePath);
    void createRequest();
    void deleteRequest();
    void renameRequest();
    void saveActiveRequest();
    void showAboutDialog();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    QString workspace;
};

#endif
