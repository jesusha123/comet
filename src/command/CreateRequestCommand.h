#ifndef CREATEREQUESTCOMMAND_H
#define CREATEREQUESTCOMMAND_H

#include "Command.h"

class RequestTabWidget;

class CreateRequestCommand : public Command
{
public:
    explicit CreateRequestCommand(RequestTabWidget* requestTabWidget);
    virtual void execute() override;
private:
    RequestTabWidget* requestTabWidget;
};

#endif // CREATEREQUESTCOMMAND_H
