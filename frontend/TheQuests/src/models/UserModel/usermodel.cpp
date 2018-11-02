#include "usermodel.h"

UserModel::UserModel(QObject *parent) : QObject(parent)
{

}

const QString& UserModel::getId() const
{
    return id;
}

void UserModel::setId(const QString &value)
{
    id = value;
}

const QString& UserModel::getNickName() const
{
    return nickName;
}

void UserModel::setNickName(const QString &value)
{
    nickName = value;
}

const QString& UserModel::getEMail() const
{
    return eMail;
}

void UserModel::setEMail(const QString &value)
{
    eMail = value;
}

const QString& UserModel::getToken() const
{
    return token;
}

void UserModel::setToken(const QString &value)
{
    token = value;
}
