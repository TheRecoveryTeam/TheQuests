//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_CARDCONTROLLER_H
#define THEQUESTS_CARDCONTROLLER_H

#include "../NetworkHelper.h"
#include "../AbstractController.h"
#include "../Handler.h"

class CardController : public networkhelper::AbstractController, networkhelper::Handler {
public:
    CardController() {
        std::wcout << U("CardController initiated");
    }

    void handleGet(http_request message) override;

    void handlePost(http_request message) override;

    void initRestOpHandlers() override;


private:
    static json::value responseNotImpl(const http::method &method);
};


#endif //THEQUESTS_CARDCONTROLLER_H
