#ifndef CARDDOANSWERRESPONSE_H
#define CARDDOANSWERRESPONSE_H

#include <QVector>
#include <QString>
#include "src/data_structures/network/ResourceItem/resourceitem.h"
#include "src/data_structures/interfaces/iserializable.h"

class QJsonObject;

namespace data_structures {

class CardDoAnswerResponse: public ISerializable
{
public:
    CardDoAnswerResponse(const QString nextCardId = "",
                         QVector<ResourceItem> resources = QVector<ResourceItem>());
    QJsonObject toJSON() const override;

    QString nextCardId;
    QVector<ResourceItem> resources;
};

}

#endif // CARDDOANSWERRESPONSE_H
