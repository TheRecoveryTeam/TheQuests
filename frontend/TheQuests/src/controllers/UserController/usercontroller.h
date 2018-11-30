#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QString>
#include <functional>
#include "../AbstractController/abstractcontoller.h"

class UserModel;

class UserController: public AbstractContoller
{
    Q_OBJECT

    typedef std::function<void(const QJsonObject&)> handleFunc;
    typedef std::function<void(bool)> isFoundFunc;
public:
    ~UserController() = default;
    static UserController* instance();

    Q_INVOKABLE void authenticate(
            const QString& email,
            const QString& password,
            const handleFunc& onErrorToFrom) const;

    Q_INVOKABLE void create(
            const QString& nickname,
            const QString& email,
            const QString& password,
            const handleFunc& onErrorToFrom) const;

    Q_INVOKABLE void logout() const;
    Q_INVOKABLE void edit(const QString& nickname, const QString& email) const;
    void findEmail(const QString& email, const isFoundFunc& onResult) const;
    void findNickname(const QString& email, const isFoundFunc& onResult) const;

private:
    static UserController* createInstance();
    explicit UserController(QObject* parent = nullptr);

    UserModel* userModel;
};

#endif // USERCONTROLLER_H
