//
// Created by dpudov on 28.10.18.
//

#ifndef APPNAME_USERCONTROLLER_H
#define APPNAME_USERCONTROLLER_H


#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT UserController : public ApplicationController {
Q_OBJECT
public:
    Q_INVOKABLE
    UserController() = default;

    UserController(const UserController &other);

public slots:

    void create();

    void login();

    void logout();

    void edit();

    void password_edit();
};


#endif //APPNAME_USERCONTROLLER_H
