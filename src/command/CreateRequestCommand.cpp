#include "CreateRequestCommand.h"
#include "RequestTabWidget.h"
#include "RequestWidget.h"

CreateRequestCommand::CreateRequestCommand(RequestTabWidget* requestTabWidget)
    : requestTabWidget(requestTabWidget)
{
}

void CreateRequestCommand::execute()
{
    auto requestWidget = new RequestWidget(requestTabWidget);
    requestTabWidget->addTab(requestWidget, "Untitled Request");
    requestTabWidget->setCurrentIndex(requestTabWidget->count()-1);
}
