#include "usercheckauthrequest.h"
#include <QJsonObject>
data_structures::UserCheckAuthRequest::UserCheckAuthRequest(const QString &token):
    token(token)
{}

QJsonObject data_structures::UserCheckAuthRequest::toJSON() const
{
    QJsonObject json;
    json["token"] = token;
    return json;
}
