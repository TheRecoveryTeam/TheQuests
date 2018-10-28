//
// Created by dpudov on 28.10.18.
//

#ifndef APPNAME_CARDCONTROLLER_H
#define APPNAME_CARDCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT CardController : public ApplicationController {
Q_OBJECT
public:
    Q_INVOKABLE
    CardController() = default;

    CardController(const CardController &other);

public slots:
    void add();

    void edit();

    void remove();

    void get();

    void do_answer();

    void list();

    void links_upsert();
};


#endif //APPNAME_CARDCONTROLLER_H
