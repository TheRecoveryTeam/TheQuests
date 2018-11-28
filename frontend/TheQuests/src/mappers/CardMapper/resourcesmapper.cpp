#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "resourcesmapper.h"


#include "src/models/structures/resourceitem.h"

QVector<structures::ResourceItem> ResourcesMapper::convertResources(const QJsonObject &obj)
{
    QVector<structures::ResourceItem> resources;
    if (obj["resources"].isArray()){
        for (auto resourceJsonItem : obj["resources"].toArray()) {
            auto resourceJsonObject = resourceJsonItem.toObject();

            if (!resourceJsonObject["type"].isString()
                    || !resourceJsonObject["value"].isDouble()) {

                // TODO: exception
            }

            structures::ResourceItem resourceItem;
            resourceItem.type = resourceJsonObject["type"].toString();
            resourceItem.value = resourceJsonObject["value"].toInt();
            resources << resourceItem;
        }
    }
    else {
        // TODO :
    }

    return resources;
}
