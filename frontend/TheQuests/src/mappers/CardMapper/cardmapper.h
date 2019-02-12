#ifndef CARDMAPPER_H
#define CARDMAPPER_H

#include <QMap>
#include <QVector>
#include "src/models/CardShortModel/cardshortmodel.h"
#include "src/models/structures/cardlink.h"

class QJsonObject;
class QString;

namespace structures {
    struct ResourceItem;
    struct CardDetail;
}

class CardMapper
{
public:
    CardMapper() = default;
    structures::CardDetail convertCardDetail(const QJsonObject& obj) const;
    QVector<QString> convertCardLinkList(const QJsonObject& obj) const;
};

#endif // CARDMAPPER_H
