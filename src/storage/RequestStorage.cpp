#include "RequestStorage.h"
#include <QDir>
#include "YamlConversions.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

bool RequestStorage::loadRequest(Request &request)
{
    qInfo() << "Loading request from" << request.filePath;

    try
    {
        // Load the YAML file
        YAML::Node yamlNode = YAML::LoadFile(request.filePath.toStdString());

        // Deserialize YAML content to the Request object using custom convert<Request>
        YAML::convert<Request>::decode(yamlNode, request);

        qInfo() << "Request loaded successfully from" << request.filePath;
        return true;
    }
    catch (const YAML::BadFile& e)
    {
        qWarning() << "Failed to load YAML file:" << QString::fromStdString(e.what());
        return false;
    }
    catch (const YAML::Exception& e)
    {
        qWarning() << "YAML Exception:" << QString::fromStdString(e.what());
        return false;
    }
    catch (...)
    {
        qWarning() << "Unknown exception occurred while loading YAML.";
        return false;
    }
}

bool RequestStorage::saveRequest(const Request &request)
{
    qInfo() << "Saving request: " << request.filePath;
    std::string path = request.filePath.toStdString();

    try
    {
        YAML::Node node = YAML::convert<Request>::encode(request);
        std::ofstream fout(path);
        if(!fout)
        {
            qWarning() << "Failed to open file for writing:" << path;
            return false;
        }
        fout << node;
        fout.close();
        return true;
    }
    catch(const YAML::Exception& e)
    {
        qWarning() << "YAML Exception:" << QString::fromStdString(e.what());
        return false;
    }
    catch(...)
    {
        qWarning() << "Unknown exception occurred while saving YAML.";
        return false;
    }
}

bool RequestStorage::deleteRequest(const QString &filePath)
{
    if (QFile::remove(filePath)) {
        qDebug() << "File deleted successfully: " << filePath;
        return true;
    } else {
        qWarning() << "Failed to delete file: " << filePath;
        return false;
    }
}

bool RequestStorage::renameRequest(const QString &prevFilePath, const QString &newFilePath)
{
    if(QFile::rename(prevFilePath, newFilePath)) {
        qDebug() << "File renamed successfully. Prev: " << prevFilePath << ", new: newFilePath";
        return true;
    } else {
        qWarning() << "Failed to rename file: " << prevFilePath;
        return false;
    }
}
