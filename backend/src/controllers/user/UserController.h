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

    void InitHandlers() override;

    void ConfigureRouting() override;


private:

    void Login(web::http::http_request message);

    void Logout(web::http::http_request message);

    void EditUser(web::http::http_request message);

    void PasswordEdit(web::http::http_request message);

    void CreateUser(const web::http::http_request& message);

    void FindEmail(const web::http::http_request& message);

    void FindNickname(const web::http::http_request& message);
};

#endif //THEQUESTS_USERCONTROLLER_H
