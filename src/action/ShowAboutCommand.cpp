#include "ShowAboutCommand.h"
#include <QMessageBox>

ShowAboutCommand::ShowAboutCommand(QWidget* parent)
    : parent(parent)
{
}

void ShowAboutCommand::execute()
{
    QMessageBox::about(parent, "Comet",
                       "<h1>Comet</h1>"
                       "<p>Version 0.0.1</p>"
                       "<p>Powered by open source software:</p>"
                       "<p>Qt 6 | License: <a href='https://doc.qt.io/qt-6/lgpl.html'>LGPL</a></p>"
                       "<p>libcurl | License: <a href='https://curl.se/docs/copyright.html'>curl license</a></p>"
    );
}
