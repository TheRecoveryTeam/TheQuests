#ifndef QUESTCREATE_H
#define QUESTCREATE_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class QJsonObject;

namespace data_structures {
class QuestCreate: public ISerializable
{
public:
    QuestCreate(const QString& title = "",
                const QString& description = "",
                const QString& imagePath = ""
                );

    QJsonObject toJSON() const override;

    QString title;
    QString description;
    QString imagePath;
};
}


#endif // QUESTCREATE_H
