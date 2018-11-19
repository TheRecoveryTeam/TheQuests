#include "cardgetrequest.h"
#include <QUrlQuery>


data_structures::CardGetRequest::CardGetRequest(const QString& cardId):
    cardId(cardId)
{ }

QString data_structures::CardGetRequest::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("cardId", cardId);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
