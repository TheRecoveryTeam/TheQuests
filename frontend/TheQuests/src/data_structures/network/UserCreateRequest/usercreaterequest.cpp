#include <QJsonObject>
#include "usercreaterequest.h"


data_structures::UserCreateRequest::UserCreateRequest(
        const QString& email,
        const QString& nickname,
        const QString& password):
    email(email), nickname(nickname), password(password)
{ }

QJsonObject data_structures::UserCreateRequest::toJSON() const
{
    QJsonObject json;
    json["email"] = email;
    json["nickname"] = nickname;
    json["password"] = password;
    return json;
}
