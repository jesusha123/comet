#ifndef RENAMEREQUESTCOMMAND_H
#define RENAMEREQUESTCOMMAND_H

#include "Command.h"

class MainWindow;
class CollectionTreeView;
class RequestTabWidget;

class RenameRequestCommand : public Command
{
public:
    explicit RenameRequestCommand(MainWindow *mainWindow, CollectionTreeView* collectionTreeView, RequestTabWidget* requestTabWidget);
    virtual void execute() override;
private:
    MainWindow *mainWindow;
    CollectionTreeView *collectionTreeView;
    RequestTabWidget *requestTabWidget;
};

#endif // RENAMEREQUESTCOMMAND_H
