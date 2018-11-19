#ifndef DATA_STRUCTURES_RESOURCEITEM_H
#define DATA_STRUCTURES_RESOURCEITEM_H

#include "src/data_structures/interfaces/iserializable.h"
#include <QString>
#include <QJsonObject>

namespace data_structures {

class ResourceItem: public ISerializable
{
public:
    ResourceItem(const QString& type = "", int value = 0);
    const ResourceItem& operator=(const ResourceItem& rhs);
    QJsonObject toJSON() const override;
    QString type;
    int value;
};

}

#endif // DATA_STRUCTURES_RESOURCEITEM_H
