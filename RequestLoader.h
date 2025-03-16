#ifndef REQUESTLOADER_H
#define REQUESTLOADER_H

#include <QObject>
#include "Request.h"

class RequestLoader : public QObject {
    Q_OBJECT
public:
    explicit RequestLoader(QObject *parent = nullptr);

    Q_INVOKABLE void loadRequestFromFile(const QString &filePath, Request *request);
};

#endif
