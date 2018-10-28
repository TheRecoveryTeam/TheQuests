#include "cardmodel.h"

CardModel::CardModel(QObject* parent):
    CardShortModel(parent),
    controller(nullptr)
{ }

CardModel::CardModel(
        const QString &id,
        const QString &questId,
        const QString &title,
        const QString &imagePath,
        const QString &description,
        const QString &type,
        AbstractCardController* controller,
        QObject* parent
    ):
    CardShortModel(id, title, imagePath, description, parent),
    questId(questId),
    type(type),
    controller(controller)
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

AbstractCardController* CardModel::getController() const
{
    return controller;
}

void CardModel::setController(AbstractCardController* value)
{
    controller = value;
}
