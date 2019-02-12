#ifndef CARDDOANSWERRESPONSE_H
#define CARDDOANSWERRESPONSE_H

#include <QVector>
#include <QString>
#include "src/models/structures/resourceitem.h"

class QJsonObject;

namespace data_structures {

class CardDoAnswerResponse
{
public:
    CardDoAnswerResponse(const QString nextCardId = "",
                         QVector<structures::ResourceItem> resources = QVector<structures::ResourceItem>());

    QString nextCardId;
    QVector<structures::ResourceItem> resources;
};

}

#endif // CARDDOANSWERRESPONSE_H
