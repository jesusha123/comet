#include "curlutils.h"

int debugFunction(CURL *, curl_infotype type, char *data, size_t size, HttpResponse* response)
{
    response->debugInfo.append(qMakePair(type, QByteArray(data, size)));
    return 0;
}

size_t writeFunction(void *data, size_t size, size_t nmemb, QByteArray* byteArray)
{
    size_t realSize = size * nmemb;
    byteArray->append((const char*)data, realSize);
    return realSize;
}

/*
 * Processes CURL header data, which includes these:
 *   - Status line
 *   - Colon separated headers
 *   - Blank line preceding response body
 */
size_t headerFunction(char *buffer, size_t size, size_t nitems, HttpResponse* response)
{
    size_t realSize = size * nitems;

    QByteArray data(buffer, realSize);
    data = data.trimmed();

    if(data.contains(':')) {
        auto split = data.split(':');
        response->headers.append(qMakePair(split.at(0), split.at(1)));
    } else if (!data.isEmpty()) {
        // We might have multiple status lines, save only the last one.
        response->statusLine.append(data);
    }

    return realSize;
}
