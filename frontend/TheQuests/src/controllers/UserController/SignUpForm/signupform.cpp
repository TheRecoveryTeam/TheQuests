#include "signupform.h"

SignUpForm::SignUpForm(QObject* parent) : LoginForm(parent),
    passwordRepeat(""),
    passwordRepeatError(""),
    passwordRepeatTouched(false)
{ }

bool SignUpForm::isValid()
{
    return LoginForm::isValid()
            && !passwordRepeat.isEmpty()
            && passwordRepeatError.isEmpty()
            && passwordRepeatTouched;
}

void SignUpForm::send()
{
    setEmail(email);
    setPassword(password);
    setPasswordRepeat(passwordRepeat);
    if (isValid()) {

    }
    else {

    }
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

void SignUpForm::validatePasswordRepeat()
{
    if (passwordRepeat != password) {
        setPasswordRepeatError(QString("Пароли не совпадают"));
    }
    else {
        setPasswordRepeatError("");
    }
}
