#include "resourceitem.h"


data_structures::ResourceItem::ResourceItem():
    type(""),
    value(0)
{

}

data_structures::ResourceItem::ResourceItem(const QString &type, int value)
{
    this->type = type;
    this->value = value;
}

const data_structures::ResourceItem&data_structures::ResourceItem::operator=(const data_structures::ResourceItem& rhs)
{
    type = rhs.type;
    value = rhs.value;
}

QJsonObject data_structures::ResourceItem::toJSON() const
{
    QJsonObject json;
    json["type"] = type;
    json["value"] = value;

    return json;
}
