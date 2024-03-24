#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include "Request.h"

namespace Ui {
class RequestWidget;
}

class RequestBuilder
{
public:
    RequestBuilder(Ui::RequestWidget* ui);
    Request buildRequest();
    void restoreRequest(const Request& request);
private:
    void addBody(Request& request);
    void addRequestHeaders(Request& request);

    Ui::RequestWidget* ui;
};

#endif // REQUESTBUILDER_H
