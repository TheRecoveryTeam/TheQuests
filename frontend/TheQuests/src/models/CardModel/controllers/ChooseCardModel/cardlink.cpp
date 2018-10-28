#include "cardlink.h"

CardLink::CardLink(QObject* parent):
    QAbstractListModel (parent)
{ }

CardLink::CardLink(const QString& answer,
                   const QVector<structures::ResourceItem>& resources,
                   QObject* parent):
    QAbstractListModel(parent),
    answer(answer),
    resources(resources)
{ }

int CardLink::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return resources.count();
}

QVariant CardLink::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= resources.count())
        return QVariant();

    switch (role) {
    case typeRole:
        return static_cast<int>(resources.at(index.row()).type);
    case valueRole:
        return resources[index.row()].value;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CardLink::rolenames() const
{
    QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[typeRole] = "type";
    roles[valueRole] = "value";
    return roles;
}

const QString& CardLink::getAnswer() const
{
    return answer;
}

void CardLink::setAnswer(const QString& value)
{
    answer = value;
}
