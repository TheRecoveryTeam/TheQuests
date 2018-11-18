//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_QUESTCONTROLLER_H
#define THEQUESTS_QUESTCONTROLLER_H

#include "../NetworkHelper.h"
#include "../AbstractController.h"
#include "../Handler.h"


class QuestController : public networkhelper::AbstractController, networkhelper::Handler {
public:
    QuestController() {
        std::wcout << U("QuestController initiated\n");
    }

    void handleGet(web::http::http_request message) override;

    void handlePost(web::http::http_request message) override;

    void initRestOpHandlers() override;


private:
    static web::json::value responseNotImpl(const web::http::method &method);
};


#endif //THEQUESTS_QUESTCONTROLLER_H
