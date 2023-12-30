#ifndef CURLUTILS_H
#define CURLUTILS_H

#include <curl/curl.h>
#include "httpresponse.h"

int debugFunction(CURL *, curl_infotype type, char *data, size_t size, HttpResponse* response);
size_t writeFunction(void *data, size_t size, size_t nmemb, QByteArray* byteArray);
size_t headerFunction(char *buffer, size_t size, size_t nitems, HttpResponse* response);
size_t readFunction(char *ptr, size_t size, size_t nmemb, QDataStream* dataStream);

#endif // CURLUTILS_H
