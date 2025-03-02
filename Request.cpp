#include "Request.h"

Request::Request(QObject *parent)
    : QObject(parent)
    , m_paramsModel(new TableModel(this))
    , m_headersModel(new TableModel(this))
{
    m_paramsModel->setColumnCount(2);
    m_headersModel->setColumnCount(2);
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

QString Request::body() const {
    return m_body;
}

void Request::setBody(const QString &body) {
    if (m_body != body) {
        m_body = body;
        emit bodyChanged();
    }
}

TableModel* Request::paramsModel() const {
    return m_paramsModel;
}

TableModel* Request::headersModel() const {
    return m_headersModel;
}
