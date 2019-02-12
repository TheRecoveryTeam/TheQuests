//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_CARDCONTROLLER_H
#define THEQUESTS_CARDCONTROLLER_H

#include <core/controller/AbstractController.h>
#include <utils/controller/Handler.h>

class CardController : public networkhelper::AbstractController {
public:
    CardController() {
        ConfigureRouting();
        std::wcout << U("CardController initiated\n");
    }

    void ConfigureRouting() override;

    void InitHandlers() override;

private:
    void AddNewCard(web::http::http_request message);

    void EditCard(web::http::http_request message);

    void RemoveCard(web::http::http_request message);

    void DoAnswer(web::http::http_request message);

    void LinksUpsert(web::http::http_request message);

    void GetCard(web::http::http_request message);

    void List(web::http::http_request message);

    void Get(web::http::http_request message);
};


#endif //THEQUESTS_CARDCONTROLLER_H
