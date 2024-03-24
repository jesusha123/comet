#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "Response.h"
#include "HttpMethod.h"

class HttpClient;
class QTableWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createRequest();
    void closeTab(int index);
    void showAboutDialog();

private:
    Ui::MainWindow *ui;
    HttpClient *httpClient;
    QStringListModel requestModel;
};

#endif
