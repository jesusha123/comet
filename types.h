#ifndef TYPES_H
#define TYPES_H

#include <QByteArray>
#include <QList>
#include <curl/curl.h>

typedef QList<QPair<curl_infotype, QByteArray>> DebugInfo;
typedef QList<QPair<QByteArray, QByteArray>> Headers;
typedef QList<QPair<QString, QString>> Info;

#endif // TYPES_H
