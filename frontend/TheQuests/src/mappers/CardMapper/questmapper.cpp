#include <QJsonObject>
#include <QJsonArray>
#include "questmapper.h"
#include "src/models/structures/questdetail.h"
#include"src/models/structures/resourceitem.h"

structures::QuestDetail QuestMapper::convertQuestDetail(const QJsonObject &obj) const
{
    structures::QuestDetail questDetail;

    if (
            obj["id"].isString()
            && obj["title"].isString()
            && obj["description"].isString()
            && obj["currCardId"].isString()
            && obj["authorNickname"].isString()
            && obj["playerCount"].isString()
            && obj["stage"].isString()) {
        questDetail.id = obj["id"].toString();
        questDetail.title = obj["title"].toString();
        questDetail.description = obj["description"].toString();
        questDetail.currCardId = obj["currCardId"].toString();
        questDetail.authorNickname = obj["authorNickname"].toString();
        questDetail.playerCount = obj["playerCount"].toString();
        questDetail.stage = obj["stage"].toString();
    }
    else {
        // TODO:
    }

    return questDetail;
}

QVector<structures::ResourceItem> QuestMapper::convertResourcesList(const QJsonArray &resourcesjsonArr) const
{
    QVector<structures::ResourceItem> resources;
    for (auto resourceJsonItem : resourcesjsonArr) {
        auto resourceJsonObj = resourceJsonItem.toObject();

        if(!resourceJsonObj["type"].isString()
                || !resourceJsonObj["value"].isString()) {
            // TODO :
        }
        else {
            structures::ResourceItem resourceItem;
            resourceItem.type = resourceJsonObj["type"].toString();
            resourceItem.value = resourceJsonObj["value"].toInt();
            resources << resourceItem;
        }
    }

    return resources;
}
