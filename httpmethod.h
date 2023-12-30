#ifndef HTTPMETHOD_H
#define HTTPMETHOD_H

#include <QString>

namespace Http {
enum Method { GET=0, HEAD=1, POST=2, PUT=3, DELETE=4, CONNECT=5, OPTIONS=6, TRACE=7, PATCH=8 };
extern QList<QString> OfficialMethods;
};


#endif // HTTPMETHOD_H
