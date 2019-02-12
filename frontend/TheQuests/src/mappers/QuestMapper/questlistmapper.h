#ifndef QUESTLISTMAPPER_H
#define QUESTLISTMAPPER_H

class QJsonArray;
class QJsonObject;

namespace structures {
    struct QuestList;
    struct QuestShort;
}
class QuestListMapper
{
public:
    QuestListMapper() = default;
    structures::QuestList convertQuestList(const QJsonObject& questListJsonObj) const;
private:
    structures::QuestShort convertQuestShort(const QJsonObject& questShortJsonObj) const;
};

#endif // QUESTLISTMAPPER_H
