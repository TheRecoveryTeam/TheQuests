#include <QJsonObject>
#include "userloginrequest.h"

data_structures::UserLoginRequest::UserLoginRequest(
        const QString& email,
        const QString& password): email(email), password(password)
{ }

QJsonObject data_structures::UserLoginRequest::toJSON() const
{
    QJsonObject json;
    json["email"] = email;
    json["password"] = password;
    return json;
}
