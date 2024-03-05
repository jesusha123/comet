#ifndef HTTPMETHOD_H
#define HTTPMETHOD_H

#include <QString>

namespace Http {

// Keep Method values and OfficialMethod indexes in sync
// DELETE is already used by Windows
enum Method { GET=0, HEAD=1, POST=2, PUT=3, DEL=4, CONNECT=5, OPTIONS=6, TRACE=7, PATCH=8 };
extern QList<QString> OfficialMethods;

enum HasBody { No=0, Yes=1, May=2 };

HasBody hasRequestBody(Method method);
HasBody hasResponseBody(Method method);

};


#endif // HTTPMETHOD_H
