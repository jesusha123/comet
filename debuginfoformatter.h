#ifndef DEBUGINFOFORMATTER_H
#define DEBUGINFOFORMATTER_H

#include "debuginfo.h"

class DebugInfoFormatter
{
public:
    DebugInfoFormatter(const DebugInfo& debugInfo);
    QString toString();
private:
    void dump(QString& target, const QByteArray& data);
    DebugInfo debugInfo;
};

#endif // DEBUGINFOFORMATTER_H
