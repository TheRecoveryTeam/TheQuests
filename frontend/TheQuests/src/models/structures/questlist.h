#ifndef QUESTLIST_H
#define QUESTLIST_H

#include <QVector>
#include <QString>
#include "src/models/structures/questshort.h"


namespace structures {
struct QuestList {
    QVector<QuestShort> quests;
    bool hasMore;
    QString stage;
};
}
#endif // QUESTLIST_H
