//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_USERCONTROLLER_H
#define THEQUESTS_USERCONTROLLER_H

#include "../AbstractController.h"
#include "../Handler.h"
#include "UserRouter.h"

class UserController : public networkhelper::AbstractController, networkhelper::Handler {
public:
    UserController() {
        std::wcout << U("UserController initiated\n");
    }

    void handleGet(web::http::http_request message) override;

    void handlePost(web::http::http_request message) override;

    void initRestOpHandlers() override;


private:
    static web::json::value responseNotImpl(const web::http::method &method);

    UserRouter _userRouter;
};

#endif //THEQUESTS_USERCONTROLLER_H
