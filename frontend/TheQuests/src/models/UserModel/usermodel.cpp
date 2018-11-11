#include "usermodel.h"
#include "src/utils/singleton.h"
UserModel::UserModel(QObject *parent) : QObject(parent)
{

}

UserModel *UserModel::createInstance()
{
    return new UserModel();
}

UserModel *UserModel::instance()
{
    return Singleton<UserModel>::instance(UserModel::createInstance);
}

UserModel::~UserModel()
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

void UserModel::setAll(const QString &id,
                       const QString &nickName,
                       const QString &eMail,
                       const QString &token)
{
    this->id = id;
    this->nickName = nickName;
    this->eMail = eMail;
    this->token = token;
}
