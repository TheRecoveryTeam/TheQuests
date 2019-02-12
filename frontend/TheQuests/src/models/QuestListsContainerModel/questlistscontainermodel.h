#ifndef QUESTLISTSCONTAINERMODEL_H
#define QUESTLISTSCONTAINERMODEL_H

#include <QObject>

class QQmlEngine;
class QJSEngine;
class QuestListModel;

class QuestListsContainerModel : QObject
{
    Q_OBJECT
public:
    static QuestListsContainerModel* instance(QQmlEngine* qmle = nullptr, QJSEngine* qjse = nullptr);
    ~QuestListsContainerModel() = default;

    QuestListModel *getInProgressQuestListModel() const;

    QuestListModel *getCompletedQuestListModel() const;

private:
    explicit QuestListsContainerModel(QObject* parent = nullptr);
    static QuestListsContainerModel* createInstance();

    QuestListModel* inProgressQuestListModel;
    QuestListModel* completedQuestListModel;
};

#endif // QUESTLISTSCONTAINERMODEL_H
