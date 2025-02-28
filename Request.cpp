#include "Request.h"

Request::Request(QObject *parent)
  : QObject(parent)
{
}

QString Request::url() const {
    return m_url;
}

void Request::setUrl(const QString &url) {
    if (m_url != url) {
        m_url = url;
        emit urlChanged();
    }
}

QString Request::method() const {
    return m_method;
}

void Request::setMethod(const QString &method) {
    if (m_method != method) {
        m_method = method;
        emit methodChanged();
    }
}
