#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "cardmapper.h"
#include "src/config/questcardtypes.h"
#include "src/models/structures/carddetail.h"
#include "src/models/structures/resourceitem.h"

structures::CardDetail CardMapper::convertCardDetail(const QJsonObject& obj) const
{
    structures::CardDetail cardDetail;

    if (
            obj["id"].isString()
            && obj["questId"].isString()
            && obj["title"].isString()
            && obj["imagePath"].isString()
            && obj["description"].isString()
            && obj["type"].isString()) {

        cardDetail.id = obj["id"].toString();
        cardDetail.questId = obj["questId"].toString();
        cardDetail.title = obj["title"].toString();
        cardDetail.imagePath = obj["imagePath"].toString();
        cardDetail.description = obj["description"].toString();
        cardDetail.type = obj["type"].toString();
    }
    else {
        // TODO: exception
    }

    return cardDetail;
}

QVector<structures::CardLink> CardMapper::convertCardLinkList(const QJsonObject& obj) const
{
    if (!obj["links"].isArray()) {
        // TODO: exception
    }

    QVector<structures::CardLink> linkList;

    QJsonArray linkListJsonArr = obj["links"].toArray();

    for (auto item: linkListJsonArr) {
        if (!item.isObject()) {
            // TODO: exception
        }

        auto itemObj = item.toObject();
        if (!itemObj["answer"].isString() || !itemObj["links"].isArray()) {
            // TODO: exception
        }

        structures::CardLink cardLink;
        cardLink.answer = itemObj["answer"].toString();

        QJsonArray resourcesJsonArr = itemObj["resources"].toArray();
        cardLink.resources = convertResourcesList(resourcesJsonArr);

        linkList << cardLink;
    }

    return linkList;
}

QVector<structures::ResourceItem> CardMapper::convertResourcesList(const QJsonArray& resourcesJsonArr)
{
    QVector<structures::ResourceItem> resources;
    for (auto resourceJsonItem: resourcesJsonArr) {
        auto resourceJsonObj = resourceJsonItem.toObject();

        if (!resourceJsonObj["type"].isString()
                || !resourceJsonObj["value"].isDouble()) {

            // TODO: exception
        }

        structures::ResourceItem resourceItem;
        resourceItem.type = resourceJsonObj["type"].toString();
        resourceItem.value = resourceJsonObj["value"].toInt();
        resources << resourceItem;
    }

    return resources;
}
