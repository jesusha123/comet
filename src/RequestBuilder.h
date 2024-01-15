#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include "Request.h"

namespace Ui {
class MainWindow;
}

class RequestBuilder
{
public:
    RequestBuilder(Ui::MainWindow* ui);
    Request buildRequest();
    void restoreRequest(const Request& request);
private:
    void addBody(Request& request);
    void addRequestHeaders(Request& request);

    Ui::MainWindow* ui;
};

#endif // REQUESTBUILDER_H
