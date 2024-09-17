#include "MainWindow.h"
#include <curl/curl.h>
#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    QApplication application(argc, argv);
    application.setApplicationName("Comet");
    application.setOrganizationDomain("comet.rest");
    application.setStyle("fusion");
    application.setWindowIcon(QIcon(":/icons/comet.ico"));
    MainWindow mainWindow;
    mainWindow.show();

    // QString workspacePath = QFileDialog::getExistingDirectory(&mainWindow,
    //                                                           "Select Workspace Folder",
    //                                                           QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    mainWindow.activateWorkspace("C:/Users/Jesus/comet");

    return application.exec();
}
