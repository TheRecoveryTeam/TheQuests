#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QString>
#include "src/utils/iform.h"

class UserController;

class LoginForm: public IForm
{
    Q_OBJECT
    Q_PROPERTY(const QString& email
               READ getEmail
               WRITE setEmail
               NOTIFY emailChanged)
    Q_PROPERTY(const QString& emailError
               READ getEmailError
               NOTIFY emailErrorChanged)
    Q_PROPERTY(const QString& password
               READ getPassword
               WRITE setPassword
               NOTIFY passwordChanged)
    Q_PROPERTY(const QString& passwordError
               READ getPasswordError
               NOTIFY passwordErrorChanged)

public:
    LoginForm(QObject* parent = nullptr);
    ~LoginForm() override = default;
    virtual bool isValid() const override;
    Q_INVOKABLE virtual void validate() override;
    Q_INVOKABLE virtual void send() override;

    const QString& getEmail() const;
    void setEmail(const QString& value);

    QString getEmailError() const;
    void setEmailError(const QString& value);

    const QString& getPassword() const;
    void setPassword(const QString& value);

    QString getPasswordError() const;
    void setPasswordError(const QString& value);

signals:
    void emailChanged(const QString&);
    void emailErrorChanged(const QString&);
    void passwordChanged(const QString&);
    void passwordErrorChanged(const QString&);

protected:
    virtual void validateEmail();
    virtual void validatePassword();

    UserController* userController;

    QString email;
    QString emailError;
    bool emailTouched;
    QString password;
    QString passwordError;
    bool passwordTouched;
};

#endif // LOGINFORM_H
