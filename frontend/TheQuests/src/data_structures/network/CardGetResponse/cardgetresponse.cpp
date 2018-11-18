#include "cardgetresponse.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QJsonValue>


data_structures::CardGetResponse::CardGetResponse()
{
    ResourceItem Res1("health", 5);
    ResourceItem Res2("shield", 10);
    ResourceItem Res3("health", 15);
    ResourceItem Res4("shield", 2);
    id = "ID";
    questId = "QUESTID";
    title = "TITLE";
    imagePath = "IMAGEPATH";
    description = "DESCRIPTION";
    links["кнопка1"] = {Res1, Res2};
    links["кнопка2"] = {Res3, Res4};
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
    QJsonArray json_array;
    while (i.hasNext()) {
        i.next();
        for (int j = 0; j < i.value().size(); ++j)
            json_array[j] = i.value()[j].toJSON();
//            json_array[j] = QJsonValue::fromVariant(QVariant::fromValue(i.value()[j]));
        links.insert(i.key(),json_array);
    }
    json["links"] = links;
    json["type"] = type;
    return json;
}
