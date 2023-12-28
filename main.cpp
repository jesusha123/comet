#include "mainwindow.h"
#include <curl/curl.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
