#include "userfindemailrequest.h"
#include <QUrlQuery>
#include <QUrl>

data_structures::UserFindEmailRequest::UserFindEmailRequest(const QString& email): email(email)
{ }

QString data_structures::UserFindEmailRequest::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("email", email);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
