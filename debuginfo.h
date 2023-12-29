#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include <QByteArray>
#include <QList>
#include <curl/curl.h>

typedef QList<QPair<curl_infotype, QByteArray>> DebugInfo;

#endif // DEBUGINFO_H
