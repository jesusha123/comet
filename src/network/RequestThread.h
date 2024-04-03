#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include <QThread>
#include "Response.h"
#include "Request.h"

class RequestThread : public QThread {
    Q_OBJECT
public:
    RequestThread(const Request& request, QObject* parent);
    void run() override;
signals:
    void responseReady(Response response);
private:
    Request request;
};

#endif
