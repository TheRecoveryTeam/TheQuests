#ifndef USERMAPPER_H
#define USERMAPPER_H

class QJsonObject;

namespace data_structures {
    struct UserCreateResponse;
    struct UserLoginResponse;
}

class UserMapper
{
public:
    UserMapper() = default;

    data_structures::UserCreateResponse convertUserCreate(const QJsonObject& obj) const;
    data_structures::UserLoginResponse convertUserLogin(const QJsonObject& obj) const;
};

#endif // USERMAPPER_H
