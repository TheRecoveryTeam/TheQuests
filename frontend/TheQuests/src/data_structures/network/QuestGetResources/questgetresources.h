#ifndef QUESTGETRESOURCES_H
#define QUESTGETRESOURCES_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {
class QuestGetResources : public IQueryable
{
public:
    explicit QuestGetResources(const QString& questId = "");
    QString toQueryString() const override;

    QString questId;
};
}


#endif // QUESTGETRESOURCES_H
