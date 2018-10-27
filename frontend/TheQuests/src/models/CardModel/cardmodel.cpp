#include "cardmodel.h"

CardModel::CardModel(QObject* parent): CardShortModel(parent)
{ }

CardModel::CardModel(
        const QString &id,
        const QString &questId,
        const QString &title,
        const QString &imagePath,
        const QString &description,
        const QString &type,
        QObject* parent
    ):
    CardShortModel(id, title, imagePath, description, parent),
    questId(questId),
    type(type)
{ }

const QString& CardModel::getQuestId() const
{
    return questId;
}

void CardModel::setQuestId(const QString &value)
{
    questId = value;
}

const QString& CardModel::getType() const
{
    return type;
}

void CardModel::setType(const QString &value)
{
    type = value;
}
