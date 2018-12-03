//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_USERCONTROLLER_H
#define THEQUESTS_USERCONTROLLER_H

#include "../AbstractController.h"
#include "../Handler.h"

class UserController : public networkhelper::AbstractController {
public:
    UserController() {
        std::wcout << U("UserController initiated\n");
    }

    void initRestOpHandlers() override;

    void ConfigureRouting() override;

    void create(web::http::http_request message);

    void login(web::http::http_request message);

    void logout(web::http::http_request message);

    void edit(web::http::http_request message);

    void password_edit(web::http::http_request message);

    void find_nickname(web::http::http_request message);

    void find_email(web::http::http_request message);


private:
    static web::json::value responseNotImpl(const web::http::method &method);
};

#endif //THEQUESTS_USERCONTROLLER_H
