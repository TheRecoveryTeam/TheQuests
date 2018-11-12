//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_HANDLER_H
#define THEQUESTS_HANDLER_H

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

namespace networkhelper {
    class Handler {
    public:
        virtual void handleGet(http_request message) = 0;

        virtual void handlePost(http_request message) = 0;
    };
}

#endif //THEQUESTS_HANDLER_H
