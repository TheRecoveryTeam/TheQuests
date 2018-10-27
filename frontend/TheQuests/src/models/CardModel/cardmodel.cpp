#include "cardmodel.h"

CardModel::CardModel(QObject* parent): QObject(parent)
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
    QObject(parent),
    id(id),
    questId(questId),
    title(title),
    imagePath(imagePath),
    description(description),
    type(type)
{ }

const QString& CardModel::getId() const
{
    return id;
}

void CardModel::setId(const QString &value)
{
    id = value;
}

const QString& CardModel::getQuestId() const
{
    return questId;
}

void CardModel::setQuestId(const QString &value)
{
    questId = value;
}

const QString& CardModel::getTitle() const
{
    return title;
}

void CardModel::setTitle(const QString &value)
{
    title = value;
}

const QString& CardModel::getImagePath() const
{
    return imagePath;
}

void CardModel::setImagePath(const QString &value)
{
    imagePath = value;
}

const QString& CardModel::getDescription() const
{
    return description;
}

void CardModel::setDescription(const QString &value)
{
    description = value;
}

const QString& CardModel::getType() const
{
    return type;
}

void CardModel::setType(const QString &value)
{
    type = value;
}
