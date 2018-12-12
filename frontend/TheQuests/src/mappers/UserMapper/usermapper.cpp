#include <QDebug>
#include <QJsonObject>
#include "usermapper.h"
#include "src/data_structures/network/UserCreateResponse/usercreateresponse.h"
#include "src/data_structures/network/UserLoginResponse/userloginresponse.h"

data_structures::UserCreateResponse UserMapper::convertUserCreate(const QJsonObject& obj) const
{
    if (obj["id"].isString() && obj["token"].isString()) {
        return data_structures::UserCreateResponse(
                    obj["id"].toString(), obj["token"].toString());
    }
    else {
        // TODO;
    }
    return data_structures::UserCreateResponse();
}

data_structures::UserLoginResponse UserMapper::convertUserLogin(const QJsonObject& obj) const
{
    if (obj["id"].isString()
            && obj["email"].isString()
            && obj["nickname"].isString()
            && obj["token"].isString()) {
        return data_structures::UserLoginResponse(
                obj["id"].toString(),
                obj["nickname"].toString(),
                obj["email"].toString(),
                obj["token"].toString());
    }
    else {
        // TODO;
    }
    return data_structures::UserLoginResponse();
}
