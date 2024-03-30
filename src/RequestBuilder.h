#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include "Request.h"

namespace Ui {
class RequestWidget;
}

class RequestBuilder
{
public:
    static Request buildRequest(std::unique_ptr<Ui::RequestWidget>& ui);
    static void restoreRequest(std::unique_ptr<Ui::RequestWidget>& ui, const Request& request);
private:
    static void addBody(std::unique_ptr<Ui::RequestWidget>& ui, Request& request);
    static void addRequestHeaders(std::unique_ptr<Ui::RequestWidget>& ui, Request& request);
};

#endif
