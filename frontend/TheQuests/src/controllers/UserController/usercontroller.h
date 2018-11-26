#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QString>
#include "../AbstractController/abstractcontoller.h"

class UserModel;

class UserController: public AbstractContoller
{
    Q_OBJECT
public:
    ~UserController() = default;
    static UserController* instance();

    Q_INVOKABLE void authenticate(const QString& email, const QString& password) const;
    Q_INVOKABLE void logout() const;
    Q_INVOKABLE void create(const QString& nickname, const QString& email, const QString& password) const;
    Q_INVOKABLE void edit(const QString& nickname, const QString& email) const;
private:
    static UserController* createInstance();
    explicit UserController(QObject* parent = nullptr);

    UserModel* userModel;
};

#endif // USERCONTROLLER_H
