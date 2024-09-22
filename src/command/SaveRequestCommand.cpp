#include <QDir>
#include <QInputDialog>
#include "RequestStorage.h"
#include "RequestTabWidget.h"
#include "RequestWidget.h"
#include "SaveRequestCommand.h"

SaveRequestCommand::SaveRequestCommand(MainWindow *mainWindow, RequestTabWidget* requestTabWidget)
    : mainWindow(mainWindow)
    , requestTabWidget(requestTabWidget)
{
}

void SaveRequestCommand::execute()
{
    RequestWidget* requestWidget = dynamic_cast<RequestWidget*>(requestTabWidget->currentWidget());
    if(requestWidget) {
        Request request = requestWidget->getRequest();
        if(ensureRequestHasFilePath(request)) {
            QFileInfo fileInfo(request.filePath);
            requestTabWidget->setTabText(requestTabWidget->currentIndex(), fileInfo.completeBaseName());
            requestWidget->setRequestFilePath(request.filePath);

            if(RequestStorage::saveRequest(request)) {
                qInfo() << "Request saved successfully";
            } else {
                qWarning() << "Error saving request";
            }
        } else {
            qInfo("Save process canceled");
        }
    } else {
        qWarning("Failed cast");
    }
}


bool SaveRequestCommand::ensureRequestHasFilePath(Request& request)
{
    bool ok = true;
    if(request.filePath.isEmpty()) {
        QString text = QInputDialog::getText(
            mainWindow,
            "Request Name",
            "Enter Request Name",
            QLineEdit::Normal,
            QString(),
            &ok);
        QDir dir(mainWindow->getFolder());
        request.filePath = dir.absoluteFilePath(text+".yaml");
    }
    return ok;
}
