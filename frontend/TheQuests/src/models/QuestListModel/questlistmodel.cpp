#include "questlistmodel.h"

QuestListModel::QuestListModel(
        QObject *parent):
    QAbstractListModel (parent)
{}

QuestListModel::QuestListModel(
        QVector<QuestShortModel*> listQuests,
        QObject *parent):
    QAbstractListModel (parent),
    listQuests(listQuests)
{}

int QuestListModel::rowCount(const QModelIndex &parent) const
{
  // TODO: разобраться
  if (parent.isValid())
      return 0;

  return listQuests.size();
}

QVariant QuestListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case questRole:
        return QVariant(QMetaType::QObjectStar, listQuests.at(index.row()));
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> QuestListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[questRole] = "quest";
    return roles;
}

void QuestListModel::add(QuestShortModel* quest)
{
    if (quest) {
        beginInsertRows(QModelIndex(), listQuests.size(), listQuests.size());
        listQuests.append(quest);
        endInsertRows();
    }
}

const QVector<QuestShortModel*>& QuestListModel::getListQuests() const
{
    return listQuests;
}

void QuestListModel::setListQuests(const QVector<QuestShortModel*> &value)
{
    listQuests = value;
}

void QuestListModel::setListQuests(const structures::QuestList value)
{
    for (auto valueItem: value.quests){
        auto questShortModel = new QuestShortModel();
        questShortModel->setId(valueItem.id);
        questShortModel->setTitle(valueItem.title);
        questShortModel->setImagePath(valueItem.imagePath);
        questShortModel->setDescription(valueItem.description);
        questShortModel->setPlayerCount(valueItem.playerCount);
        questShortModel->setAuthorNickName(valueItem.authorNickname);

        listQuests << questShortModel;
    }
}

