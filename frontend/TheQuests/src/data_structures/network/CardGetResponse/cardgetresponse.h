#ifndef CARDGETRESPONSE_H
#define CARDGETRESPONSE_H

#include "src/data_structures/interfaces/iserializable.h"
#include "src/data_structures/network/ResourceItem/resourceitem.h"
#include <QString>
#include <QMap>
#include <QVector>


namespace data_structures {

    class CardGetResponse : public ISerializable
    {
    public:
        explicit CardGetResponse();
        QJsonObject toJSON() const override;

    private:
        QString id;
        QString questId;
        QString title;
        QString imagePath;
        QString description;
        QMap<QString, QVector<ResourceItem>>  links;
        QString type;
    };

}


#endif // CARDGETRESPONSE_H
