#include "cardlinklist.h"

CardLinkList::CardLinkList(QObject* parent): QAbstractListModel(parent)
{ }

CardLinkList::CardLinkList(const QVector<CardLink*>& links, QObject* parent):
    QAbstractListModel(parent),
    links(links)
{ }

int CardLinkList::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return links.count();
}

QVariant CardLinkList::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= links.count())
        return QVariant();

    switch (role) {
    case linkRole:
        return QVariant(QMetaType::QObjectStar, links[index.row()]);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CardLinkList::rolenames() const
{
    QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[linkRole] = "link";
    return roles;
}
