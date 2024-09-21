#ifndef SAVEREQUESTCOMMAND_H
#define SAVEREQUESTCOMMAND_H

#include "Command.h"
#include "MainWindow.h"
#include "Request.h"

class RequestTabWidget;

class SaveRequestCommand : public Command
{
public:
    explicit SaveRequestCommand(MainWindow *mainWindow, RequestTabWidget *requestTabWidget);
    virtual void execute() override;
private:
    bool ensureRequestHasFilePath(Request& request);

    MainWindow *mainWindow;
    RequestTabWidget* requestTabWidget;
};

#endif // SAVEREQUESTCOMMAND_H
