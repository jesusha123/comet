#ifndef LOADREQUESTCOMMAND_H
#define LOADREQUESTCOMMAND_H

#include "Command.h"
#include <QString>

class RequestTabWidget;

class LoadRequestCommand : public Command
{
public:
    explicit LoadRequestCommand(const QString &filePath, RequestTabWidget *requestTabWidget);
    virtual void execute() override;
private:
    QString filePath;
    RequestTabWidget* requestTabWidget;
};

#endif // LOADREQUESTCOMMAND_H
