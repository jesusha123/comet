#include "RequestFileManager.h"
#include <QFile>

RequestFileManager::RequestFileManager(QObject *parent)
    : QObject(parent)
{
}

void RequestFileManager::loadRequestFromFile(const QString &filePath, Request *request) {
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

Q_INVOKABLE bool RequestFileManager::saveRequestToFile(const QString &filePath, Request *request) {
    if (!request) {
        qWarning() << "Request pointer is null!";
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    // Write YAML document start marker
    out << "---\n";
    // Write key/value pairs. Enclose values in quotes if necessary.
    out << "url: \"" << request->url() << "\"\n";
    out << "method: \"" << request->method() << "\"\n";
    out << "body: \"" << request->body() << "\"\n";

    file.close();
    return true;
}
