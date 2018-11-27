#ifndef QUESTGETREQUEST_H
#define QUESTGETREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {

class QuestGetRequest: public IQueryable
{
public:
    explicit QuestGetRequest(const QString& questId = "");
    QString toQueryString() const override;

    QString questId;
};

}
#endif // QUESTGETREQUEST_H
