#include "carddoanswerresponse.h"
#include <QJsonObject>
#include <QJsonArray>


data_structures::CardDoAnswerResponse::CardDoAnswerResponse(
        const QString nextCardId,
        QVector<structures::ResourceItem> resources
):
    nextCardId(nextCardId),
    resources(resources)
{ }
