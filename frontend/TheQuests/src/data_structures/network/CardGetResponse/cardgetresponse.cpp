#include "cardgetresponse.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QJsonValue>


data_structures::CardGetResponse::CardGetResponse()
{
    ResourceItem res1("health", 5);
    ResourceItem res2("shield", 10);
    ResourceItem res3("health", 15);
    ResourceItem res4("shield", 2);
    id = "ID";
    questId = "QUESTID";
    title = "TITLE";
    imagePath = "IMAGEPATH";
    description = "DESCRIPTION";
    QVector<data_structures::ResourceItem> vec1;

    vec1.push_back(res1);
    vec1.push_back(res2);
    links.insert("btn1", vec1);

    QVector<data_structures::ResourceItem> vec2;
    vec2.push_back(res3);
    vec2.push_back(res4);
    links["btn2"] = vec2;

    type = "FINISH";
}

QJsonObject data_structures::CardGetResponse::toJSON() const
{
    QJsonObject json;
    json["id"] = id;
    json["questId"] = questId;
    json["title"] = title;
    json["imagePath"] = imagePath;
    json["description"] = description;

    QJsonObject links;

    QMapIterator<QString, QVector<ResourceItem>> i(this->links);

    while (i.hasNext()) {
        i.next();
        QJsonArray arr;
        for (int j = 0; j < i.value().size(); ++j) {
            arr << i.value()[j].toJSON();
        }
        links[i.key()] = arr;
    }


    json["links"] = links;
    json["type"] = type;
    return json;
}
