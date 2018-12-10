#include <QDebug>
#include <QQmlEngine>
#include <QJSEngine>
#include "questdetailmodel.h"
#include "src/utils/singleton.h"
#include "src/models/structures/questdetail.h"
#include "src/models/ResourceListModel/resourcelistmodel.h"

QuestDetailModel::QuestDetailModel(QObject *parent):
    QuestShortModel (parent),
    resources(nullptr)
{}

ResourceListModel* QuestDetailModel::getResources() const
{
    return resources;
}

void QuestDetailModel::setResources(ResourceListModel* value)
{
    if (resources) {
        resources->deleteLater();
    }
    if (value) {
        value->setParent(this);
    }
    resources = value;
    emit resourcesChanged(resources);
}

QuestDetailModel *QuestDetailModel::createInstance()
{
    return new QuestDetailModel();
}

QuestDetailModel *QuestDetailModel::instance(QQmlEngine* qqmle, QJSEngine* qjse)
{
    return Singleton<QuestDetailModel>::instance(QuestDetailModel::createInstance);
}

const QString& QuestDetailModel::getCurrCardId() const
{
    return currCardId;
}

void QuestDetailModel::setCurrCardId(const QString &value)
{
    currCardId = value;
    emit currCardIdChanged(currCardId);
}

const QString& QuestDetailModel::getStage() const
{
    return stage;
}

void QuestDetailModel::setStage(const QString &value)
{
    stage = value;
    emit stageChanged(stage);
}

void QuestDetailModel::setAll(const QString &id,
                              const QString &title,
                              const QString &description,
                              const QString &authorNickName,
                              const QString &playerCount,
                              const QString &imagePath,
                              const QString &currCardId,
                              const QString &stage)
{
    setId(id);
    setTitle(title);
    setDescription(description);
    setAuthorNickName(authorNickName);
    setPlayerCount(playerCount);
    setImagePath(imagePath);
    setCurrCardId(currCardId);
    setStage(stage);
}

void QuestDetailModel::setQuestDetail(structures::QuestDetail &questDetail)
{
    setId(questDetail.id);
    setTitle(questDetail.title);
    setDescription(questDetail.description);
    setAuthorNickName(questDetail.authorNickname);
    setPlayerCount(questDetail.playerCount);
    setImagePath(questDetail.imagePath);
    setCurrCardId(questDetail.currCardId);
    setStage(questDetail.stage);
    qDebug() << "in setQuestDetail";
    setResources(new ResourceListModel(questDetail.resources, this));
}
