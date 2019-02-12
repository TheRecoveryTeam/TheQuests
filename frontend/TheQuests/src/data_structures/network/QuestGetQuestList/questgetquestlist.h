#ifndef QUESTGETQUESTLIST_H
#define QUESTGETQUESTLIST_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {
class QuestGetQuestList : public IQueryable
{
public:
    explicit QuestGetQuestList(const QString& page = "",
                               const QString& limit = "",
                               const QString& authorId = "",
                               const QString& = "",
                               const QString& stage = "");
    QString toQueryString() const override;


    QString page;
    QString limit;
    QString authorId;
    QString asc;
    QString stage;
};
}

#endif // QUESTGETQUESTLIST_H
