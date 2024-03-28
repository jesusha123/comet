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
private:
    static void addBody(std::unique_ptr<Ui::RequestWidget>& ui, Request& request);
    static void addRequestHeaders(std::unique_ptr<Ui::RequestWidget>& ui, Request& request);
};

#endif
