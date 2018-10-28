//
// Created by dpudov on 28.10.18.
//

#ifndef APPNAME_QUESTCONTROLLER_H
#define APPNAME_QUESTCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT QuestController : public ApplicationController {
Q_OBJECT
public:
    Q_INVOKABLE
    QuestController() = default;

    QuestController(const QuestController &other);

public slots:

    void create();

    void destroy();

    void edit();

    void edit_image();

    void detail();

    void resources();

    void list();
};


#endif //APPNAME_QUESTCONTROLLER_H
