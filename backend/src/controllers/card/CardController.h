//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_CARDCONTROLLER_H
#define THEQUESTS_CARDCONTROLLER_H

#include "../AbstractController.h"
#include "../Handler.h"
#include "CardRouter.h"

class CardController : public networkhelper::AbstractController, networkhelper::Handler {
public:
    CardController() {
        std::wcout << U("CardController initiated\n");
    }

    void handleGet(web::http::http_request message) override;

    void handlePost(web::http::http_request message) override;

    void initRestOpHandlers() override;


private:
    static web::json::value responseNotImpl(const web::http::method &method);

    CardRouter _cardRouter;
};


#endif //THEQUESTS_CARDCONTROLLER_H
