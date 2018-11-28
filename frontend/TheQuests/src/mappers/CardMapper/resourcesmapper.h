#ifndef RESOURCESMAPPER_H
#define RESOURCESMAPPER_H

#include <QVector>

class QJsonObject;
namespace structures {
    struct ResourceItem;
}
class ResourcesMapper
{
public:
    ResourcesMapper() = default;
    QVector<structures::ResourceItem> convertResources (const QJsonObject& obj);
};

#endif // RESOURCESMAPPER_H
