#include "userfindnicknamerequest.h"
#include <QUrlQuery>
#include <QUrl>

data_structures::UserFindNicknameRequest::UserFindNicknameRequest(const QString& nickname): nickname(nickname)
{ }

QString data_structures::UserFindNicknameRequest::toQueryString() const
{
    QUrlQuery query;
    query.addQueryItem("nickname", nickname);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}
