#include "http_method.h"
#include <QList>

QStringList Http::OfficialMethods({ "GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS", "TRACE", "PATCH" });

Http::HasBody Http::hasRequestBody(Method method) {
    switch(method) {
    case GET: case HEAD: case CONNECT: case OPTIONS: case TRACE:
        return No;
    case POST: case PUT: case PATCH:
        return Yes;
    case DELETE:
        return May;
    }
}

Http::HasBody Http::hasResponseBody(Method method) {
    switch(method) {
    case HEAD: case CONNECT: case TRACE:
        return No;
    case GET: case POST: case OPTIONS:
        return Yes;
    case PUT: case DELETE: case PATCH:
        return May;
    }
}
