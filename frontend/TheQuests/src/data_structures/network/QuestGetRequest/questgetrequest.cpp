#include "questgetrequest.h"
#include <QUrlQuery>

data_structures::QuestGetRequest::QuestGetRequest(const QString &questId):
    questId(questId)
{}

QString data_structures::QuestGetRequest::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("questId", questId);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
