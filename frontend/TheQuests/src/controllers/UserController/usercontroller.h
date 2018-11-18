#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QString>
#include "../AbstractController/abstractcontoller.h"
#include "src/models/UserModel/usermodel.h"

class UserController: public AbstractContoller
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent = nullptr);
    ~UserController();

    void authenticate(const QString& email, const QString& password) const;
    void logout() const;
    void create(const QString& nickname, const QString& email, const QString& password) const;
    void edit(const QString& nickname, const QString& email) const;
private:
    UserModel* userModel;
};

#endif // USERCONTROLLER_H