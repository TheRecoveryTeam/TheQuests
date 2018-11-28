#include <QJsonObject>
#include "usereditrequest.h"

data_structures::UserEditRequest::UserEditRequest(
        const QString& nickname,
        const QString& email): nickname(nickname), email(email)
{ }

QJsonObject data_structures::UserEditRequest::toJSON() const
{
    QJsonObject json;
    json["nickname"] = nickname;
    json["email"] = email;
    return json;
}
