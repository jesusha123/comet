#include "LoadRequestCommand.h"
#include <QFileInfo>
#include "RequestStorage.h"
#include "RequestTabWidget.h"
#include "RequestWidget.h"

LoadRequestCommand::LoadRequestCommand(const QString &filePath, RequestTabWidget *requestTabWidget)
    : filePath(filePath)
    , requestTabWidget(requestTabWidget)
{
}

void LoadRequestCommand::execute()
{
    qInfo() << "Selected file:" << filePath;
    int tabIndex = requestTabWidget->findRequestTab(filePath);

    if(tabIndex >= 0) {
        requestTabWidget->setCurrentIndex(tabIndex);
    } else {
        Request request;
        request.filePath = filePath;
        if (RequestStorage::loadRequest(request)) {
            auto requestWidget = new RequestWidget(requestTabWidget);
            requestWidget->restoreRequest(request);

            QFileInfo fileInfo(request.filePath);

            requestTabWidget->addTab(requestWidget, fileInfo.completeBaseName());
            requestWidget->setRequestFilePath(request.filePath);
            requestTabWidget->setCurrentIndex(requestTabWidget->count()-1);
        } else {
            qWarning() << "Error loading request";
        }
    }

}
