#include "cardlinklist.h"

CardLinkList::CardLinkList(QObject* parent): QAbstractListModel(parent)
{ }

CardLinkList::CardLinkList(const QVector<CardLink*>& links, QObject* parent):
    QAbstractListModel(parent),
    links(links)
{ }

int CardLinkList::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return links.count();
}

QVariant CardLinkList::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= links.count()) {
        return QVariant();
    }

    if (role == linkRole || role == Qt::DisplayRole) {
        return QVariant::fromValue(links[index.row()]);
    }
    return QVariant();
}

bool CardLinkList::appendLink(CardLink* link)
{
    if (!link) {
        return false;
    }
    emit beginInsertRows(QModelIndex(), links.count(), links.count());
    this->links << link;
    emit endInsertRows();
    return true;
}

QHash<int, QByteArray> CardLinkList::roleNames() const
{
    QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[linkRole] = "link";
    return roles;
}
