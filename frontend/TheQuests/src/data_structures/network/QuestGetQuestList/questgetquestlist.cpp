#include "questgetquestlist.h"
#include <QUrlQuery>

data_structures::QuestGetQuestList::QuestGetQuestList(const QString &page,
                                                      const QString &limit,
                                                      const QString &authorId,
                                                      const QString &asc,
                                                      const QString &stage):
    page(page),
    limit(limit),
    authorId(authorId),
    asc(asc),
    stage(stage)
{}

QString data_structures::QuestGetQuestList::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("page", page);
    query.addQueryItem("limit", limit);
    query.addQueryItem("authorId", authorId);
    query.addQueryItem("asc", asc);
    query.addQueryItem("stage", stage);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
