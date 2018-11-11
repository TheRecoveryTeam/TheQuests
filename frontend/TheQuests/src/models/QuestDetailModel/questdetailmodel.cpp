#include "questdetailmodel.h"
#include "src/utils/singleton.h"


QuestDetailModel::QuestDetailModel(QObject *parent):
    QuestShortModel (parent)
{}

QuestDetailModel *QuestDetailModel::createInstance()
{
    return new QuestDetailModel();
}

QuestDetailModel::~QuestDetailModel()
{

}

QuestDetailModel *QuestDetailModel::instance()
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
}

const QString& QuestDetailModel::getStage() const
{
    return stage;
}

void QuestDetailModel::setStage(const QString &value)
{
    stage = value;
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
    this->id = id;
    this->title = title;
    this->description = description;
    this->authorNickName = authorNickName;
    this->playerCount = playerCount;
    this->imagePath = imagePath;
    this->currCardId = currCardId;
    this->stage = stage;
}
