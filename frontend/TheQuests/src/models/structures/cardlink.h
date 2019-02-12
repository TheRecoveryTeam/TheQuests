#ifndef AACARDLINK_H
#define AACARDLINK_H

#include <QString>
#include <QVector>
#include "resourceitem.h"

namespace structures {

struct CardLink {
    QString answer = "";
    QVector<ResourceItem> resources = QVector<ResourceItem>();
};

}

#endif // CARDLINK_H
