#include "questgetresources.h"
#include <QUrlQuery>

data_structures::QuestGetResources::QuestGetResources(const QString &questId):
    questId(questId)
{}

QString data_structures::QuestGetResources::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("questId", questId);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
