#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include "Request.h"

namespace Ui {
class RequestWidget;
}

class RequestBuilder
{
public:
    static std::unique_ptr<Request> buildRequest(std::unique_ptr<Ui::RequestWidget>& ui);
private:
    static void addBody(std::unique_ptr<Ui::RequestWidget>& ui, std::unique_ptr<Request>& request);
    static void addRequestHeaders(std::unique_ptr<Ui::RequestWidget>& ui, std::unique_ptr<Request>& request);
};

#endif
