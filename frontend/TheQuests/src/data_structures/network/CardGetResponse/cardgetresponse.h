#ifndef CARDGETRESPONSE_H
#define CARDGETRESPONSE_H

#include <QString>
#include <QMap>
#include <QVector>
#include "src/data_structures/network/ResourceItem/resourceitem.h"
#include "src/data_structures/interfaces/iserializable.h"

namespace data_structures {

class CardGetResponse: public ISerializable
{
public:
    explicit CardGetResponse();
    QJsonObject toJSON() const override;

    QString id;
    QString questId;
    QString title;
    QString imagePath;
    QString description;
    QMap<QString, QVector<ResourceItem>> links;
    QString type;
};

}


#endif // CARDGETRESPONSE_H
