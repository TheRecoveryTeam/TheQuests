#include "questlistscontainermodel.h"
#include <QQmlEngine>
#include <QJSEngine>
#include "src/utils/singleton.h"

QuestListsContainerModel *QuestListsContainerModel::instance(QQmlEngine *qmle, QJSEngine *qjse)
{
    return Singleton<QuestListsContainerModel>::instance(QuestListsContainerModel::createInstance);
}

QuestListsContainerModel::QuestListsContainerModel(QObject *parent):
    QObject (parent)
{

}

QuestListsContainerModel *QuestListsContainerModel::createInstance()
{
    return new QuestListsContainerModel();
}

QuestListModel *QuestListsContainerModel::getCompletedQuestListModel() const
{
    return completedQuestListModel;
}

QuestListModel *QuestListsContainerModel::getInProgressQuestListModel() const
{
    return inProgressQuestListModel;
}
