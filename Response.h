#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QStandardItemModel>
#include <QtQml/qqmlregistration.h>
#include "TableModel.h"

class Response : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int statusCode READ statusCode WRITE setStatusCode NOTIFY statusCodeChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(TableModel* headersModel READ headersModel CONSTANT)
public:
    explicit Response(QObject *parent = nullptr);

    int statusCode() const;
    void setStatusCode(int statusCode);

    QString body() const;
    void setBody(const QString &body);

    TableModel* headersModel() const;
signals:
    void statusCodeChanged();
    void bodyChanged();
private:
    int m_statusCode;
    QString m_body;
    TableModel* m_headersModel;
};

#endif
