#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "httpresponse.h"
#include "httprequest.h"

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
    void sendRequest();
    void processResponse(const HttpResponse& response);
    void processParams(const QString& url);
    void processParamsChanged(QTableWidgetItem *item);
    void processParamsRemoved();

private:
    void initializeCollection();
    void initializeConnections();
    void initializeHeaderTables();
    void initializeMethodComboBox();
    void addRequestHeaders(HttpRequest& request);
    void buildParamsLineEdit();

    Ui::MainWindow *ui;
    HttpClient *httpClient;
};
#endif // MAINWINDOW_H
