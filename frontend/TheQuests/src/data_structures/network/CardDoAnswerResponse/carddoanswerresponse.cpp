#include "carddoanswerresponse.h"
#include <QJsonObject>
#include <QJsonArray>


data_structures::CardDoAnswerResponse::CardDoAnswerResponse(
        const QString nextCardId,
        QVector<data_structures::ResourceItem> resources
):
    nextCardId(nextCardId),
    resources(resources)
{ }

QJsonObject data_structures::CardDoAnswerResponse::toJSON() const
{
    QJsonObject json;
    json["nextCardId"] = nextCardId;

    QJsonArray resources;
    for (auto& res: this->resources) {
        resources << res.toJSON();
    }

    json["resources"] = resources;
    return json;
}
