#ifndef QUESTSHORT_H
#define QUESTSHORT_H

#include <QString>

namespace structures {

struct QuestShort {
    QString id = "";
    QString title = "";
    QString description = "";
    QString authorNickname = "";
    QString playerCount = "";
    QString imagePath = "";
};

}
#endif // QUESTSHORT_H
