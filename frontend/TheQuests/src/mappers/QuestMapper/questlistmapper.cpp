#include "questlistmapper.h"
#include <QJsonArray>
#include <QJsonObject>
#include "src/models/structures/questlist.h"
#include "src/models/structures/questshort.h"
#include <QVector>

structures::QuestList QuestListMapper::convertQuestList(const QJsonObject &questListJsonObj) const
{
    structures::QuestList questList;
    if (!questListJsonObj["quests"].isArray()
            || !questListJsonObj["hasMore"].isBool()) {
        // TODO :
    }
    else {
        for (auto questShortItem : questListJsonObj["quests"].toArray()) {
            auto questShortObj = questShortItem.toObject();
            questList.quests << convertQuestShort(questShortObj);
        }
        questList.hasMore = questListJsonObj["hasMore"].toBool();
    }

    return questList;
}

structures::QuestShort QuestListMapper::convertQuestShort(const QJsonObject &questShortJsonObj) const
{
    structures::QuestShort questShort;

    if (
            questShortJsonObj["id"].isString()
            && questShortJsonObj["title"].isString()
            && questShortJsonObj["description"].isString()
            && questShortJsonObj["authorNickname"].isString()
            && questShortJsonObj["playerCount"].isString()
            && questShortJsonObj["imagePath"].isString()) {

        questShort.id =  questShortJsonObj["id"].toString();
        questShort.title =  questShortJsonObj["title"].toString();
        questShort.description =  questShortJsonObj["description"].toString();
        questShort.authorNickname =  questShortJsonObj["authorNickname"].toString();
        questShort.playerCount =  questShortJsonObj["playerCount"].toString();
        questShort.imagePath =  questShortJsonObj["imagePath"].toString();
    }
    else {
        // TODO :
    }

    return questShort;
}
