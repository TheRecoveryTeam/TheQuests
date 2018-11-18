//
// Created by dpudov on 18.11.18.
//

#ifndef THEQUESTS_USERROUTER_H
#define THEQUESTS_USERROUTER_H

#include "../AbstractRequestRouter.h"

class UserRouter : public networkhelper::AbstractRequestRouter {
public:
    void ConfigureRouting() override;

    void route_get_request(web::http::http_request message) override;

    void route_post_request(web::http::http_request message) override;
};


#endif //THEQUESTS_USERROUTER_H
