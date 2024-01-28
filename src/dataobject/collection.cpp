#include "collection.h"

Collection::Collection(const QString &name)
    : name(name)
{
}

Collection::~Collection()
{
    qDeleteAll(requestList);
}

bool Collection::isEmpty() const
{
    return requestList.empty();
}

int Collection::getSize() const
{
    return requestList.size();
}

void Collection::append(Request *request)
{
    requestList.append(request);
}

QString Collection::getName() const
{
    return name;
}
