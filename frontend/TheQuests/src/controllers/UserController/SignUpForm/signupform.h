#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QObject>
#include "../LoginForm/loginform.h"

class SignUpForm : public LoginForm
{
    Q_OBJECT
    Q_PROPERTY(const QString& passwordRepeat
               READ getPasswordRepeat
               WRITE setPasswordRepeat
               NOTIFY passwordRepeatChanged)
    Q_PROPERTY(const QString& passwordRepeatError
               READ getPasswordRepeatError
               WRITE setPasswordRepeatError
               NOTIFY passwordRepeatErrorChanged)

public:
    explicit SignUpForm(QObject *parent = nullptr);

    bool isValid() override;
    Q_INVOKABLE void send() override;

    QString getPasswordRepeat() const;
    void setPasswordRepeat(const QString& value);

    QString getPasswordRepeatError() const;
    void setPasswordRepeatError(const QString& value);

signals:
    void passwordRepeatChanged(const QString&);
    void passwordRepeatErrorChanged(const QString&);

private:
    void validatePasswordRepeat();

    QString passwordRepeat;
    QString passwordRepeatError;
    bool passwordRepeatTouched;
};

#endif // SIGNUPFORM_H
