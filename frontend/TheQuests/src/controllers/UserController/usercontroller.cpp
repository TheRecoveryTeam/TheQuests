#include <QDebug>
#include <QJsonObject>
#include "src/config/apiurls.h"
#include "usercontroller.h"
#include "src/models/UserModel/usermodel.h"
#include "src/utils/singleton.h"
#include "src/engine/HttpRequester/httprequester.h"
#include "src/data_structures/network/UserLoginRequest/userloginrequest.h"
#include "src/data_structures/network/UserLoginResponse/userloginresponse.h"
#include "src/data_structures/network/UserCreateRequest/usercreaterequest.h"
#include "src/data_structures/network/UserCreateResponse/usercreateresponse.h"
#include "src/data_structures/network/UserFindEmailReqeust/userfindemailrequest.h"
#include "src/data_structures/network/UserFindNicknameReqeust/userfindnicknamerequest.h"
#include "src/mappers/UserMapper/usermapper.h"


UserController*UserController::instance()
{
    return Singleton<UserController>::instance(UserController::createInstance);
}

void UserController::authenticate(const QString& email, const QString& password, const UserController::handleFunc& onErrorToFrom) const
{
    auto handleSuccess = [this](QJsonObject obj){
        UserMapper mapper;
        auto response = mapper.convertUserLogin(obj);
        userModel->setAll(
                    response.id,
                    response.nickname,
                    response.email,
                    response.token);
        qDebug() << obj << response.id << response.nickname << response.email << response.token;
        httpRequester->setToken(response.token);
    };

    auto hanldeError = [onErrorToFrom](QJsonObject obj){
        qDebug() << obj;
        onErrorToFrom(obj);
    };

    httpRequester->doPost(config::apiUrls::user::LOGIN,
                data_structures::UserLoginRequest(email, password),
                handleSuccess, hanldeError);
}

void UserController::logout() const
{
    auto handleLogout = [this](QJsonObject){
        httpRequester->setToken("");
        userModel->setAll("", "", "", "");
    };

    httpRequester->doPost(
                config::apiUrls::user::LOGOUT,
                handleLogout, handleLogout);
}

void UserController::create(const QString& nickname, const QString& email, const QString& password,
                            const UserController::handleFunc& onErrorToFrom) const
{
    auto handleSuccess = [this, nickname, email](QJsonObject obj) {
        auto mapper = UserMapper();
        auto response = mapper.convertUserCreate(obj);
        httpRequester->setToken(response.token);
        userModel->setAll(response.id, nickname, email, response.token);
    };

    auto handleError = [onErrorToFrom](QJsonObject obj) {
        qDebug() << obj;
        onErrorToFrom(obj);
    };

    httpRequester->doPost(
                config::apiUrls::user::CREATE,
                data_structures::UserCreateRequest(email, nickname, password),
                handleSuccess, handleError);
}

void UserController::edit(const QString& nickname, const QString& email) const
{

}

void UserController::findEmail(const QString& email, const UserController::isFoundFunc& onResult) const
{
    httpRequester->doGet(config::apiUrls::user::FIND_EMAIL,
                         data_structures::UserFindEmailRequest(email),
    [onResult](QJsonObject obj){
        qDebug() << "email found";
        onResult(true);
    },
    [onResult](QJsonObject obj){
        qDebug() << "email not found";
        onResult(false);
    });
}

void UserController::findNickname(const QString& nickname, const UserController::isFoundFunc& onResult) const
{
    httpRequester->doGet(config::apiUrls::user::FIND_NICKNAME,
                         data_structures::UserFindNicknameRequest(nickname),
    [onResult](QJsonObject obj){
        onResult(true);
    },
    [onResult](QJsonObject obj){
        onResult(false);
    });
}

UserController*UserController::createInstance()
{
    return new UserController();
}

UserController::UserController(QObject* parent):
    AbstractContoller (parent, HttpRequester::instance()),
    userModel(UserModel::instance())
{}

