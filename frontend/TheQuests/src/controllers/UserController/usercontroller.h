#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QString>
#include <functional>
#include "../AbstractController/abstractcontoller.h"

class UserModel;
class QJsonObject;

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
    Q_INVOKABLE void checkAuth(const QString& userId,
                               const QString& nickname,
                               const QString& email,
                               const QString& vkId,
                               const QString& token,
                               const QString& avatarPath) const;
    void findEmail(const QString& email, const isFoundFunc& onResult) const;
    void findNickname(const QString& email, const isFoundFunc& onResult) const;

    Q_INVOKABLE void processOauth(const QString& oauthRedirectPath) const;

signals:
    void authorized(const QString& userId,
                    const QString& nickname,
                    const QString& email,
                    const QString& vkId,
                    const QString& token,
                    int expires,
                    const QString& avatarPath) const;

    void loggedOut() const;

private:
    static UserController* createInstance();
    explicit UserController(QObject* parent = nullptr);

    std::function<void(QJsonObject)> handleSuccessAuthorized;
    UserModel* userModel;
};

#endif // USERCONTROLLER_H
