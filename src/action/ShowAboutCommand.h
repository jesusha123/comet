#ifndef SHOWABOUTCOMMAND_H
#define SHOWABOUTCOMMAND_H

#include <QWidget>
#include "Command.h"

class ShowAboutCommand : public Command {
public:
    ShowAboutCommand(QWidget* parent);
    virtual void execute() override;
private:
    QWidget *parent;
};

#endif
