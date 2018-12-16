//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_HANDLER_H
#define THEQUESTS_HANDLER_H

#include <cpprest/http_msg.h>

namespace networkhelper {
    class Handler {
    public:
        virtual void handleGet(web::http::http_request message) = 0;

        virtual void handlePost(web::http::http_request message) = 0;
    };
}

#endif //THEQUESTS_HANDLER_H
