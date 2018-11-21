#ifndef QUESTDETAIL_H
#define QUESTDETAIL_H

#include <QString>

namespace structures {

struct QuestDetail {
    QString id = "";
    QString title = "";
    QString description = "";
    QString currCardId = "";
    QString authorNickname = "";
    QString playerCount = "";
    QString stage = "";
};
}

#endif // QUESTDETAIL_H
