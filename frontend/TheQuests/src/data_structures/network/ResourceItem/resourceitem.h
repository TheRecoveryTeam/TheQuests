#ifndef RESOURCEITEM_H
#define RESOURCEITEM_H
#include "src/data_structures/interfaces/iserializable.h"
#include <QString>
#include <QJsonObject>


class ResourceItem : public ISerializable
{
public:
    ResourceItem();
    ResourceItem(const QString& type, int value);
    QJsonObject toJSON() const override;
private:
    QString type;
    int value;
};

#endif // RESOURCEITEM_H
