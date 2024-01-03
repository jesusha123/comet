#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include "httprequest.h"

namespace Ui {
class MainWindow;
}

class RequestBuilder
{
public:
    RequestBuilder(Ui::MainWindow* ui);
    HttpRequest buildRequest();
private:
    void addBody(HttpRequest& request);
    void addRequestHeaders(HttpRequest& request);

    Ui::MainWindow* ui;
};

#endif // REQUESTBUILDER_H
