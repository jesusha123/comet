#ifndef COLLECTION_H
#define COLLECTION_H

#include <QList>

class Request;

class Collection {
public:
    Collection(const QString& name);
    ~Collection();
    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;
    Collection(Collection&&) = delete;
    Collection& operator=(Collection&&) = delete;

    bool isEmpty() const;
    int getSize() const;
    void append(Request* request);
    QString getName() const;
private:
    QString name;
    QList<Request*> requestList;
};

#endif // COLLECTION_H
