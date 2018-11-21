#ifndef QUESTLIST_H
#define QUESTLIST_H

#include <QVector>
#include "src/models/structures/questshort.h"


namespace structures {
struct QuestList {
    QVector<QuestShort> quests;
    bool hasMore;
};
}
#endif // QUESTLIST_H
