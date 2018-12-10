#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include "cardmapper.h"
#include "src/config/questcardtypes.h"
#include "src/models/structures/carddetail.h"
#include "src/models/structures/resourceitem.h"

structures::CardDetail CardMapper::convertCardDetail(const QJsonObject& obj) const
{
    structures::CardDetail cardDetail;

    if (
            obj["id"].isString()
            && obj["questId"].isString()
            && obj["title"].isString()
            && obj["imagePath"].isString()
            && obj["description"].isString()
            && obj["type"].isString()) {

        cardDetail.id = obj["id"].toString();
        cardDetail.questId = obj["questId"].toString();
        cardDetail.title = obj["title"].toString();
        cardDetail.imagePath = obj["imagePath"].toString();
        cardDetail.description = obj["description"].toString();
        cardDetail.type = obj["type"].toString();
    }
    else {
        // TODO: exception
    }

    return cardDetail;
}

QVector<QString> CardMapper::convertCardLinkList(const QJsonObject& obj) const
{
    if (!obj["links"].isArray()) {
        // TODO: exception
    }

    QVector<QString> linkList;

    QJsonArray linkListJsonArr = obj["links"].toArray();

    for (auto item: linkListJsonArr) {
        if (!item.isString()) {
            // TODO: exception
        }
        linkList << item.toString();
    }

    return linkList;
}
