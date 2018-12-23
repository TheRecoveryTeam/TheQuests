#include <QJsonObject>
#include <QJsonArray>
#include "questmapper.h"
#include "resourcesmapper.h"
#include "src/models/structures/questdetail.h"
#include "src/models/structures/resourceitem.h"

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
            && obj["stage"].isString()
            && obj["imagePath"].isString()
            && obj["resources"].isArray()) {
        questDetail.id = obj["id"].toString();
        questDetail.title = obj["title"].toString();
        questDetail.description = obj["description"].toString();
        questDetail.currCardId = obj["currCardId"].toString();
        questDetail.authorNickname = obj["authorNickname"].toString();
        questDetail.playerCount = obj["playerCount"].toString();
        questDetail.stage = obj["stage"].toString();
        questDetail.imagePath = obj["imagePath"].toString();
        questDetail.resources = ResourcesMapper().convertResources(obj);
    }
    else {
        // TODO:
    }

    return questDetail;
}

