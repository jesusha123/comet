#ifndef DELETEREQUESTCOMMAND_H
#define DELETEREQUESTCOMMAND_H

#include "Command.h"

class CollectionTreeView;
class RequestTabWidget;

class DeleteRequestCommand : public Command
{
public:
    explicit DeleteRequestCommand(CollectionTreeView* collectionTreeView, RequestTabWidget *requestTabWidget);
    virtual void execute() override;
private:
    CollectionTreeView* collectionTreeView;
    RequestTabWidget* requestTabWidget;
};

#endif // DELETEREQUESTCOMMAND_H
