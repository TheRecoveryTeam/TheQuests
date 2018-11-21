//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_QUESTCONTROLLER_H
#define THEQUESTS_QUESTCONTROLLER_H

#include "../AbstractController.h"
#include "../Handler.h"

class QuestController : public networkhelper::AbstractController {
public:
    QuestController() {
        std::wcout << U("QuestController initiated\n");
    }

    void initRestOpHandlers() override;

    void ConfigureRouting() override;

    void create(web::http::http_request message);

    void destroy(web::http::http_request message);

    void edit(web::http::http_request message);

    void edit_image(web::http::http_request message);

    void detail(web::http::http_request message);

    void resources(web::http::http_request message);

    void list(web::http::http_request message);

private:
    static web::json::value responseNotImpl(const web::http::method &method);

};


#endif //THEQUESTS_QUESTCONTROLLER_H
