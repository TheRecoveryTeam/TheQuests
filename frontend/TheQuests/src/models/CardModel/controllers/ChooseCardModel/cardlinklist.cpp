#include "cardlinklist.h"
#include <QDebug>

CardLinkList::CardLinkList(QObject* parent): QAbstractListModel(parent)
{ }

CardLinkList::CardLinkList(const QVector<QString>& links, QObject* parent):
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
        return links[index.row()];
    }
    return QVariant();
}

bool CardLinkList::appendLink(const QString& link)
{
    emit beginInsertRows(QModelIndex(), links.count(), links.count());
    links << link;
    emit endInsertRows();
    return true;
}

QHash<int, QByteArray> CardLinkList::roleNames() const
{
    QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[linkRole] = "link";
    return roles;
}
