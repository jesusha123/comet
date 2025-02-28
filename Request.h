#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class Request : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
public:
    explicit Request(QObject *parent = nullptr);

    QString url() const;
    void setUrl(const QString &url);

    QString method() const;
    void setMethod(const QString &method);

    QString body() const;
    void setBody(const QString &body);
signals:
    void urlChanged();
    void methodChanged();
    void bodyChanged();
private:
    QString m_url;
    QString m_method;
    QString m_body;
};

#endif
