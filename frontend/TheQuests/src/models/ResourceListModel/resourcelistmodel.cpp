#include "resourcelistmodel.h"
//#include "src/models/structures/resourceitem.h"

ResourceListModel::ResourceListModel(
        const QVector<structures::ResourceItem>& resources,
        QObject* parent):
    QAbstractListModel(parent),
    resources(resources)
{ }

ResourceListModel::ResourceListModel(QObject* parent): QAbstractListModel(parent)
{
}

int ResourceListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return resources.count();
}

QVariant ResourceListModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    if(index.row() >= resources.count()) {
        return QVariant();
    }

    if (role == nameRole) {
        return resources[index.row()].name;
    }

    if (role == valueRole) {
        return resources[index.row()].value;
    }

    return QVariant();
}

QHash<int, QByteArray> ResourceListModel::roleNames() const
{
    QHash <int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[nameRole] = "name";
    roles[valueRole] = "value";
    return roles;
}


