#include "MainWindow.h"
#include <curl/curl.h>
#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    QApplication application(argc, argv);
    application.setOrganizationName("Comet");
    application.setOrganizationDomain("comet.rest");
    application.setApplicationName("Comet");
    application.setStyle("fusion");
    application.setWindowIcon(QIcon(":/icons/comet.ico"));
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.loadFolder();

    return application.exec();
}
