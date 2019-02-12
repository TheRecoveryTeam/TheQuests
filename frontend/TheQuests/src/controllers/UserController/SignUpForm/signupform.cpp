#include "signupform.h"
#include "../usercontroller.h"

SignUpForm::SignUpForm(QObject* parent) : LoginForm(parent),
    passwordRepeat(""),
    passwordRepeatError(""),
    passwordRepeatTouched(false)
{ }

void SignUpForm::validate()
{
    LoginForm::validate();
    validatePasswordRepeat();
}

bool SignUpForm::isValid() const
{
    return LoginForm::isValid()
            && !passwordRepeat.isEmpty()
            && passwordRepeatError.isEmpty()
            && passwordRepeatTouched;
}

QString SignUpForm::getPasswordRepeat() const
{
    return passwordRepeat;
}

void SignUpForm::setPasswordRepeat(const QString& value)
{
    passwordRepeat = value;
    passwordRepeatTouched = true;
    emit passwordRepeatChanged(passwordRepeat);
    validatePasswordRepeat();
}

QString SignUpForm::getPasswordRepeatError() const
{
    return passwordRepeatError;
}

void SignUpForm::setPasswordRepeatError(const QString& value)
{
    passwordRepeatError = value;
    emit passwordRepeatErrorChanged(passwordRepeatError);
}

void SignUpForm::validateEmail()
{
    LoginForm::validateEmail();
    if (emailError == "") {
        this->userController->findEmail(email, [this](bool found){
            if (found) {
                this->setEmailError("Данный email уже занят");
            }
            else {
                this->setEmailError("");
            }
            emit this->isValidChanged(this->isValid());
        });
    }
}

void SignUpForm::validatePassword()
{
    const int minPassworLenght = 8;
    if (password.size() < minPassworLenght) {
        setPasswordError(QString("Пароль слишком короткий"));
    }
    else {
        setPasswordError("");
    }
    isValidChanged(isValid());
}

void SignUpForm::validatePasswordRepeat()
{
    if (passwordRepeat != password) {
        setPasswordRepeatError(QString("Пароли не совпадают"));
    }
    else {
        setPasswordRepeatError("");
    }
    isValidChanged(isValid());
}
