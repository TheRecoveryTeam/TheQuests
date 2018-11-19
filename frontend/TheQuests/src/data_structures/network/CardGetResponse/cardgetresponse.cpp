#include "cardgetresponse.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QJsonValue>


data_structures::CardGetResponse::CardGetResponse(
        const QString& id,
        const QString& questId,
        const QString& title,
        const QString& imagePath,
        const QString& description,
        const QMap<QString, QVector<ResourceItem> >& links,
        const QString& type
        ): id(id), questId(questId), title(title), imagePath(imagePath), description(description), links(links), type(type)
{ }

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
