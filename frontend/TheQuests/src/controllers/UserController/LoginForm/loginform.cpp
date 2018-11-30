#include <QRegExp>
#include <QDebug>
#include <QJsonObject>
#include "loginform.h"
#include "../usercontroller.h"

LoginForm::LoginForm(QObject* parent):
    IForm (parent),
    userController(UserController::instance()),
    email(""),
    emailError(""),
    emailTouched(false),
    password(""),
    passwordError(""),
    passwordTouched(false)
{ }

bool LoginForm::isValid() const
{
    // Для того, чтобы даже если поля еще не touched они стали touched
    // и испустились все необходимые сигналы
    return emailTouched
            && passwordTouched
            && emailError.isEmpty()
            && passwordError.isEmpty()
            && !email.isEmpty()
            && !password.isEmpty();
}

void LoginForm::validate()
{
    validateEmail();
    validatePassword();
    emit isValidChanged(isValid());
}

void LoginForm::send()
{
    if (isValid()) {
        userController->authenticate(email, password, [this](const QJsonObject& obj) {
            if (obj["emailError"].isString()) {
                this->setEmailError(obj["emailError"].toString());
            }
            if (obj["passwordError"].isString()) {
                this->setPasswordError(obj["passwordError"].toString());
            }
        });
    }
    else {
        qDebug() << "form not valid";
    }
}

const QString& LoginForm::getEmail() const
{
    return email;
}

void LoginForm::setEmail(const QString& value)
{
    email = value;
    emailTouched = true;
    emit emailChanged(email);
    validateEmail();
}

QString LoginForm::getEmailError() const
{
    return emailTouched ? emailError : "";
}

void LoginForm::setEmailError(const QString& value)
{
    emailError = value;
    emit emailErrorChanged(emailError);
}

const QString& LoginForm::getPassword() const
{
    return password;
}

void LoginForm::setPassword(const QString& value)
{
    password = value;
    passwordTouched = true;
    emit passwordChanged(password);
    validatePassword();
}

QString LoginForm::getPasswordError() const
{
    return passwordTouched ? passwordError : "";
}

void LoginForm::setPasswordError(const QString& value)
{
    passwordError = value;
    passwordErrorChanged(passwordError);
}

void LoginForm::validateEmail()
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(email)) {
        setEmailError(QString("Некорректный email"));
    }
    else {
        setEmailError("");
    }
    isValidChanged(isValid());
}

void LoginForm::validatePassword()
{
    if (password.size() == 0) {
        setPasswordError(QString("Заполните пароль"));
    }
    else {
        setPasswordError("");
    }
    isValidChanged(isValid());
}
