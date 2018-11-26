#include <QRegExp>
#include <QDebug>
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
{

}

bool LoginForm::isValid()
{
    return emailTouched
            && passwordTouched
            && emailError.isEmpty()
            && passwordError.isEmpty()
            && !email.isEmpty()
            && !password.isEmpty();
}

void LoginForm::send()
{
    // Для того, чтобы даже если поля еще не touched они стали touched
    // и испустились все необходимые сигналы
    setEmail(email);
    setPassword(password);
    if (isValid()) {
        qDebug() << "should send";
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
}

void LoginForm::validatePassword()
{
    const int minPassworLenght = 8;
    if (password.size() < minPassworLenght) {
        setPasswordError(QString("Пароль слишком короткий"));
    }
    else {
        setPasswordError("");
    }
}
