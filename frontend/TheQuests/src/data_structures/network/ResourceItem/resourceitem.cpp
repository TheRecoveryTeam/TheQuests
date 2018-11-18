#include "resourceitem.h"


ResourceItem::ResourceItem():
    type(""),
    value(0)
{

}

ResourceItem::ResourceItem(const QString &type, int value)
{
    this->type = type;
    this->value = value;
}

QJsonObject ResourceItem::toJSON() const
{
    QJsonObject json;
    json["type"] = type;
    json["value"] = value;

    return json;
}
