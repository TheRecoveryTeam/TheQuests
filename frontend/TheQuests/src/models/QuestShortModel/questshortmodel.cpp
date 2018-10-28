#include "questshortmodel.h"

QuestShortModel::QuestShortModel(QObject *parent) : QObject(parent)
{

}

QuestShortModel::QuestShortModel(
        const QString &id,
        const QString &title,
        const QString &description,
        const QString &authorNickName,
        const QString &playerCount,
        const QString &imagePath,
        QObject *parent
    ):
    QObject (parent),
    id(id),
    title(title),
    description(description),
    authorNickName(authorNickName),
    playerCount(playerCount),
    imagePath(imagePath)
{}

const QString& QuestShortModel::getId() const
{
    return id;
}

void QuestShortModel::setId(const QString &value)
{
    id = value;
}

const QString& QuestShortModel::getTitle() const
{
    return title;
}

void QuestShortModel::setTitle(const QString &value)
{
    title = value;
}

const QString& QuestShortModel::getDescription() const
{
    return description;
}

void QuestShortModel::setDescription(const QString &value)
{
    description = value;
}

const QString& QuestShortModel::getAuthorNickName() const
{
    return authorNickName;
}

void QuestShortModel::setAuthorNickName(const QString &value)
{
    authorNickName = value;
}

const QString& QuestShortModel::getPlayerCount() const
{
    return playerCount;
}

void QuestShortModel::setPlayerCount(const QString &value)
{
    playerCount = value;
}

const QString& QuestShortModel::getImagePath() const
{
    return imagePath;
}

void QuestShortModel::setImagePath(const QString &value)
{
    imagePath = value;
}
