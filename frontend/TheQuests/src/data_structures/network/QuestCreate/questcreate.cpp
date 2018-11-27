#include "questcreate.h"
#include <QJsonObject>

data_structures::QuestCreate::QuestCreate(const QString &title,
                                          const QString &description,
                                          const QString &imagePath):
    title(title),
    description(description),
    imagePath(imagePath)
{

}

QJsonObject data_structures::QuestCreate::toJSON() const
{
    QJsonObject json;
    json["title"] = title;
    json["description"] = description;
    json["imagePath"] = imagePath;

    return json;
}
