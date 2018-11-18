//
// Created by dpudov on 18.11.18.
//

#ifndef THEQUESTS_CARDROUTER_H
#define THEQUESTS_CARDROUTER_H


#include "../AbstractRequestRouter.h"

class CardRouter : public networkhelper::AbstractRequestRouter {
    bool isValid(web::http::http_request message) override;

    void route_post_request(web::http::http_request message) override;

    void route_get_request(web::http::http_request message) override;
};


#endif //THEQUESTS_CARDROUTER_H
