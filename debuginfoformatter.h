#ifndef DEBUGINFOFORMATTER_H
#define DEBUGINFOFORMATTER_H

#include "types.h"

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
