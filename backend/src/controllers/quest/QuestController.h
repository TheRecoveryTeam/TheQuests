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

    void InitHandlers() override;

    void ConfigureRouting() override;

private:
    void CreateQuest(web::http::http_request message);

    void DestroyQuest(web::http::http_request message);

    void EditQuest(web::http::http_request message);

    void EditQuestImage(web::http::http_request message);

    void GetQuest(web::http::http_request message);

    void Resources(web::http::http_request message);

    void List(web::http::http_request message);
};


#endif //THEQUESTS_QUESTCONTROLLER_H
