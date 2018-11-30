#include "signupfinishform.h"
#include "../usercontroller.h"
#include <QJsonObject>

SignUpFinishForm::SignUpFinishForm(
        const QString& email,
        const QString& password,
        QObject* parent):
    IForm(parent),
    userController(UserController::instance()),
    email(email),
    password(password)
{ }

void SignUpFinishForm::initialize(const QString& email, const QString& password)
{
    this->email = email;
    this->password = password;
}

void SignUpFinishForm::validate()
{
    validateNickname();
}

void SignUpFinishForm::send()
{
    userController->create(nickname, email, password, [](QJsonObject obj){
        // TODO
    });
}

bool SignUpFinishForm::isValid() const
{
    return nicknameError == ""
            && nicknameTouched
            && !nickname.isEmpty();
}

QString SignUpFinishForm::getNickname() const
{
    return nickname;
}

void SignUpFinishForm::setNickname(const QString& value)
{
    nickname = value;
    nicknameTouched = true;
    emit nicknameChanged(nickname);
    validateNickname();
}

QString SignUpFinishForm::getNicknameError() const
{
    return nicknameError;
}

void SignUpFinishForm::setNicknameError(const QString& value)
{
    nicknameError = value;
    emit nicknameErrorChanged(nicknameError);
}

void SignUpFinishForm::validateNickname()
{
    if (nickname.isEmpty()) {
        setNicknameError(QString("Заполните поле"));
        emit isValidChanged(false);
    }
    else {
        userController->findNickname(nickname, [this](bool found) {
            if (found) {
                this->setNicknameError(QString("Этот никнейм уже занят"));
            }
            else {
                this->setNicknameError("");
            }
            emit this->isValidChanged(!found);
        });
    }
}
