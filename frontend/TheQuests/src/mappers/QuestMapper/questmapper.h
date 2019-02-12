#ifndef QUESTMAPPER_H
#define QUESTMAPPER_H

#include <QVector>
class QJsonObject;
class QJsonArray;

namespace structures {
    struct QuestDetail;
    struct ResourceItem;
}

class QuestMapper
{
public:
    QuestMapper() = default;
    structures::QuestDetail convertQuestDetail (const QJsonObject& obj) const;
};

#endif // QUESTMAPPER_H
