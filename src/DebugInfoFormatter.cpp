#include "DebugInfoFormatter.h"

DebugInfoFormatter::DebugInfoFormatter(const DebugInfo& debugInfo)
    : debugInfo(debugInfo)
{
}

QString DebugInfoFormatter::toString()
{
    QString text;

    for(const auto &debugInfoPair : debugInfo) {
        switch(debugInfoPair.first) {
        case CURLINFO_TEXT:
            text.append("== Info: ");
            text.append(debugInfoPair.second);
        default:
            continue;

        case CURLINFO_HEADER_OUT:
            text.append("=> Send header");
            break;
        case CURLINFO_DATA_OUT:
            text.append("=> Send data");
            break;
        case CURLINFO_SSL_DATA_OUT:
            text.append("=> Send SSL data");
            break;
        case CURLINFO_HEADER_IN:
            text.append("<= Recv header");
            break;
        case CURLINFO_DATA_IN:
            text.append("<= Recv data");
            break;
        case CURLINFO_SSL_DATA_IN:
            text.append("<= Recv SSL data");
            break;
        }

        dump(text, debugInfoPair.second);
    }

    return text;
}

void DebugInfoFormatter::dump(QString& target, const QByteArray& data)
{
    unsigned int width = 0x10;
    unsigned int dataSize = data.size();
    QChar fill = '0';

    target.append(QString(", %1 bytes (0x%2)\n").arg(dataSize, 10, 10, fill).arg(dataSize, 8, 16, fill));
    for(int i = 0; i < data.size(); i+=width) {
        target.append(QString("%1: ").arg(i, 4, 16, fill));

        for(unsigned int c = 0; c < width; c++) {
            if(i + c < dataSize) {
                target.append(QString("%1 ").arg(data[i+c] & 0xff, 2, 16, fill));
            } else {
                target.append("   ");
            }
        }

        for(unsigned int c = 0; (c < width) && (i + c < dataSize); c++) {
            char x = (data[i + c] >= 0x20) ? data[i + c] : '.';
            target.append(x);
        }

        target.append('\n');
    }
}
