//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_USERCONTROLLER_H
#define THEQUESTS_USERCONTROLLER_H

#include "../NetworkHelper.h"
#include "../AbstractController.h"
#include "../Handler.h"

class UserController : public networkhelper::AbstractController, networkhelper::Handler {
public:
    UserController() {
        std::wcout << U("UserController initiated\n");
    }

    void handleGet(http_request message) override;

    void handlePost(http_request message) override;

    void initRestOpHandlers() override;


private:
    static json::value responseNotImpl(const http::method &method);
};

#endif //THEQUESTS_USERCONTROLLER_H
