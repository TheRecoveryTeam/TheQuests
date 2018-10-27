#include "questdetailmodel.h"



QuestDetailModel::QuestDetailModel(QObject *parent):
    QuestShortModel (parent)
{

}

QuestDetailModel::QuestDetailModel(
        const QString &id,
        const QString &title,
        const QString &description,
        const QString &authorNickName,
        const QString &playerCount,
        const QString &imagePath,
        const QString &currCardId,
        const QString &stage,
        QObject *parent
    ):
    QuestShortModel(
        id,
        title,
        description,
        authorNickName,
        playerCount,
        imagePath,
        parent),
    currCardId(currCardId),
    stage(stage)
{}

const QString& QuestDetailModel::getCurrCardId() const
{
    return currCardId;
}

void QuestDetailModel::setCurrCardId(const QString &value)
{
    currCardId = value;
}

const QString& QuestDetailModel::getStage() const
{
    return stage;
}

void QuestDetailModel::setStage(const QString &value)
{
    stage = value;
}
