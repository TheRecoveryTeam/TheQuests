//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_CARDCONTROLLER_H
#define THEQUESTS_CARDCONTROLLER_H

#include "../AbstractController.h"
#include "../Handler.h"

class CardController : public networkhelper::AbstractController {
public:
    CardController() {
        ConfigureRouting();
        std::wcout << U("CardController initiated\n");
    }

    void ConfigureRouting() override;

    void initRestOpHandlers() override;

    void add(web::http::http_request message);

    void edit(web::http::http_request message);

    void remove(web::http::http_request message);

    void do_answer(web::http::http_request message);

    void links_upsert(web::http::http_request message);

    void get(web::http::http_request message);

    void list(web::http::http_request message);

private:
    static web::json::value responseNotImpl(const web::http::method &method);

};


#endif //THEQUESTS_CARDCONTROLLER_H
