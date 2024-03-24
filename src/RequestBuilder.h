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
    std::unique_ptr<Request> buildRequest();
    void restoreRequest(const Request& request);
private:
    void addBody(std::unique_ptr<Request>& request);
    void addRequestHeaders(std::unique_ptr<Request>& request);

    Ui::RequestWidget* ui;
};

#endif // REQUESTBUILDER_H
