#ifndef SIGNUPFINISHFORM_H
#define SIGNUPFINISHFORM_H

#include <QString>
#include "src/utils/iform.h"

class UserController;

class SignUpFinishForm : public IForm
{
    Q_OBJECT
    Q_PROPERTY(const QString& nickname
               READ getNickname
               WRITE setNickname
               NOTIFY nicknameChanged)
    Q_PROPERTY(const QString& nicknameError
               READ getNicknameError
               NOTIFY nicknameErrorChanged)
public:
    SignUpFinishForm(const QString& email = "",
                     const QString& password = "",
                     QObject* parent = nullptr);
    ~SignUpFinishForm() override = default;
    Q_INVOKABLE void initialize(const QString& email, const QString& password);
    bool isValid() const override;
    Q_INVOKABLE void validate() override;
    Q_INVOKABLE void send() override;

    QString getNickname() const;
    void setNickname(const QString& value);

    QString getNicknameError() const;
    void setNicknameError(const QString& value);

signals:
    void nicknameChanged(const QString&);
    void nicknameErrorChanged(const QString&);

private:
    void validateNickname();

    UserController* userController;

    QString nickname;
    QString nicknameError;
    bool nicknameTouched;

    // нужны для отправки формы, передаются извне
    QString email;
    QString password;
};

#endif // SIGNUPFINISHFORM_H
