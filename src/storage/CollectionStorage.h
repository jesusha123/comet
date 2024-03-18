#ifndef COLLECTIONSTORAGE_H
#define COLLECTIONSTORAGE_H

#include "Request.h"
#include "Collection.h"

class CollectionStorage
{
public:
    CollectionStorage();
    Collection* loadFromFile(const QString& filePath);
private:
};

#endif // COLLECTIONSTORAGE_H
