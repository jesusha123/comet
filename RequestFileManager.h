#ifndef REQUESTFILEMANAGER_H
#define REQUESTFILEMANAGER_H

#include <QObject>
#include "Request.h"

class RequestFileManager : public QObject {
    Q_OBJECT
public:
    explicit RequestFileManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadRequestFromFile(const QString &filePath, Request *request);
    Q_INVOKABLE bool saveRequestToFile(const QString &filePath, Request *request);
};

#endif
