#include "RequestLoader.h"
#include <QFile>

RequestLoader::RequestLoader(QObject *parent)
    : QObject(parent)
{
}

void RequestLoader::loadRequestFromFile(const QString &filePath, Request *request) {
    if (!request) {
        qWarning() << "Request pointer is null!";
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("---") || line.startsWith("#"))
            continue;

        int colonIndex = line.indexOf(':');
        if (colonIndex == -1)
            continue;

        QString key = line.left(colonIndex).trimmed();
        QString value = line.mid(colonIndex + 1).trimmed();
        if ((value.startsWith("\"") && value.endsWith("\"")) ||
            (value.startsWith("'") && value.endsWith("'"))) {
            value = value.mid(1, value.length() - 2);
        }

        // Update the Request object based on the key
        if (key == "url")
            request->setUrl(value);
        else if (key == "method")
            request->setMethod(value);
        else if (key == "body")
            request->setBody(value);
    }
    file.close();
}
