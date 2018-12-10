#ifndef RESOURCELISTMODEL_H
#define RESOURCELISTMODEL_H

#include <QAbstractListModel>
#include "src/models/structures/resourceitem.h"

class ResourceListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        nameRole = Qt::UserRole + 1,
        valueRole
    };

    ResourceListModel(const QVector<structures::ResourceItem>& resources,
                      QObject* parent = nullptr);
    ResourceListModel(QObject* parent = nullptr);
    ~ResourceListModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash <int, QByteArray> roleNames() const;

private:
    QVector<structures::ResourceItem> resources;
};

#endif // RESOURCELISTMODEL_H
