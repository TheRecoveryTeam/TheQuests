#include <QDebug>
#include "usermodel.h"
#include "src/utils/singleton.h"


UserModel::UserModel(QObject *parent) : QObject(parent), token("")
{ }

UserModel *UserModel::createInstance()
{
    return new UserModel();
}

const QString& UserModel::getAvatarPath() const
{
    return avatarPath;
}

void UserModel::setAvatarPath(const QString& value)
{
    avatarPath = value;
    emit avatarPathChanged(avatarPath);
}

UserModel *UserModel::instance()
{
    return Singleton<UserModel>::instance(UserModel::createInstance);
}

UserModel::~UserModel()
{ }

const QString& UserModel::getId() const
{
    return id;
}

void UserModel::setId(const QString &value)
{
    id = value;
    emit idChanged(id);
}

const QString& UserModel::getNickname() const
{
    return nickname;
}

void UserModel::setNickname(const QString &value)
{
    nickname = value;
    emit nicknameChanged(nickname);
}

const QString& UserModel::getEmail() const
{
    return email;
}

void UserModel::setEmail(const QString &value)
{
    email = value;
    emit emailChanged(email);
}

const QString& UserModel::getToken() const
{
    return token;
}

void UserModel::setToken(const QString &value)
{
    qDebug() << "set token" << value;
    token = value;
    emit tokenChanged(token);
}

bool UserModel::isAuthenticated() const
{
    qDebug() << "is authenticated " << !token.isEmpty() << token;
    return !token.isEmpty();
}

void UserModel::setAll(const QString &id,
                       const QString &nickname,
                       const QString &email,
                       const QString &token,
                       const QString &avatarPath)
{
    setId(id);
    setNickname(nickname);
    setEmail(email);
    setToken(token);
    setAvatarPath(avatarPath);
}
