#ifndef YAMLCONVERSIONS_H
#define YAMLCONVERSIONS_H

#include "Request.h"
#include <yaml-cpp/yaml.h>

namespace YAML {
template<>
struct convert<Request> {
    static Node encode(const Request& req) {
        Node node;
        node["url"] = req.url.toString().toStdString();
        node["method"] = req.method.toStdString();
        node["body"] = req.body.toStdString();

        Node headersNode(YAML::NodeType::Sequence);
        for(const auto& header : req.headers)
        {
            Node headerMap;
            headerMap["key"] = header.first.toStdString();
            headerMap["value"] = header.second.toStdString();
            headersNode.push_back(headerMap);
        }
        node["headers"] = headersNode;

        return node;
    }

    static bool decode(const Node& node, Request& req) {
        if(!node.IsMap()) return false;

        if(node["url"])
            req.url = QUrl(QString::fromStdString(node["url"].as<std::string>()));
        else
            req.url = QUrl();

        if(node["method"])
            req.method = QString::fromStdString(node["method"].as<std::string>());
        else
            req.method.clear();

        if(node["body"])
            req.body = QByteArray::fromStdString(node["body"].as<std::string>());
        else
            req.body.clear();

        req.headers.clear();
        if(node["headers"] && node["headers"].IsSequence())
        {
            for(const auto& headerNode : node["headers"])
            {
                if(headerNode.IsMap())
                {
                    QString key = headerNode["key"] ? QString::fromStdString(headerNode["key"].as<std::string>()) : QString();
                    QString value = headerNode["value"] ? QString::fromStdString(headerNode["value"].as<std::string>()) : QString();
                    req.headers.append(qMakePair(key, value));
                }
            }
        }

        return true;
    }
};
}

#endif // YAMLCONVERSIONS_H
