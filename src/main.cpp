#include "MainWindow.h"
#include <curl/curl.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    QApplication app(argc, argv);
    application.setApplicationName("Comet");
    application.setOrganizationDomain("comet.rest");
    application.setStyle("fusion");
    application.setWindowIcon(QIcon(":/icons/comet.ico"));
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
