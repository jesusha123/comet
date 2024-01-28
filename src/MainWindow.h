#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "response.h"
#include "http_method.h"
#include "RequestStorage.h"

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
    void saveRequest();
    void readRequest();
    void processResponse(const Response& response);
    void processParams(const QString& url);
    void processParamsChanged(QTableWidgetItem *item);
    void processParamsRemoved();
    void processRequestBodyAllowed(Http::HasBody reqHasBody);
    void processReqContentTypeChange(int index);

private:
    void initializeCollection();
    void initializeConnections();
    void buildParamsLineEdit();

    Ui::MainWindow *ui;
    HttpClient *httpClient;
    RequestStorage requestStorage;
};
#endif // MAINWINDOW_H
