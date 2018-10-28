#include "usermodel.h"

UserModel::UserModel(QObject *parent) : QObject(parent)
{

}

QString UserModel::getId() const
{
    return id;
}

void UserModel::setId(const QString &value)
{
    id = value;
}

QString UserModel::getNickName() const
{
    return nickName;
}

void UserModel::setNickName(const QString &value)
{
    nickName = value;
}

QString UserModel::getEMail() const
{
    return eMail;
}

void UserModel::setEMail(const QString &value)
{
    eMail = value;
}

QString UserModel::getToken() const
{
    return token;
}

void UserModel::setToken(const QString &value)
{
    token = value;
}
