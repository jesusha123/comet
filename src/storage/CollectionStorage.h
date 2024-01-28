#ifndef COLLECTIONSTORAGE_H
#define COLLECTIONSTORAGE_H

#include "request.h"
#include "collection.h"

class CollectionStorage
{
public:
    CollectionStorage();
    Collection* loadFromFile(const QString& filePath);
private:
};

#endif // COLLECTIONSTORAGE_H
