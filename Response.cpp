#include "Response.h"

Response::Response(QObject *parent)
    : QObject(parent)
    , m_statusCode(0)
    , m_headersModel(new TableModel(this))
{
}

int Response::statusCode() const {
    return m_statusCode;
}

void Response::setStatusCode(int statusCode) {
    if (m_statusCode != statusCode) {
        m_statusCode = statusCode;
        emit statusCodeChanged();
    }
}

QString Response::body() const {
    return m_body;
}

void Response::setBody(const QString &body) {
    if (m_body != body) {
        m_body = body;
        emit bodyChanged();
    }
}

TableModel* Response::headersModel() const {
    return m_headersModel;
}
