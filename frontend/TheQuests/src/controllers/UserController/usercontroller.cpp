#include "usercontroller.h"
#include "src/models/UserModel/usermodel.h"
#include "src/utils/singleton.h"
#include "src/engine/HttpRequester/httprequester.h"


UserController*UserController::instance()
{
    return Singleton<UserController>::instance(UserController::createInstance);
}

void UserController::authenticate(const QString& email, const QString& password) const
{

}

void UserController::logout() const
{

}

void UserController::create(const QString& nickname, const QString& email, const QString& password) const
{

}

void UserController::edit(const QString& nickname, const QString& email) const
{

}

UserController*UserController::createInstance()
{
    return new UserController();
}

UserController::UserController(QObject* parent):
    AbstractContoller (parent, HttpRequester::instance()),
    userModel(UserModel::instance())
{}

