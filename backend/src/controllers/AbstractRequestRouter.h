//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_REQUESTROUTER_H
#define THEQUESTS_REQUESTROUTER_H


#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

namespace networkhelper {
    class AbstractRequestRouter {
    public:
        AbstractRequestRouter();

        ~AbstractRequestRouter();

    private:
        virtual bool isValid(web::http::http_request message) = 0;

        virtual void route_get_request(web::http::http_request message) = 0;

        virtual void route_post_request(web::http::http_request message) = 0;
    };
}


#endif //THEQUESTS_REQUESTROUTER_H
