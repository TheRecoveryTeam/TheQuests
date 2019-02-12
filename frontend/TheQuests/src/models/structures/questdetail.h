#ifndef QUESTDETAIL_H
#define QUESTDETAIL_H

#include <QString>
#include <QVector>
#include "resourceitem.h"

namespace structures {

struct QuestDetail {
    QString id = "";
    QString title = "";
    QString description = "";
    QString currCardId = "";
    QString authorNickname = "";
    QString playerCount = "";
    QString imagePath = "";
    QString stage = "";
    QVector<ResourceItem> resources;
};
}

#endif // QUESTDETAIL_H
