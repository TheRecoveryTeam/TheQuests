//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_REQUESTROUTER_H
#define THEQUESTS_REQUESTROUTER_H


#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class RequestRouter {
public:
    RequestRouter();

private:
    bool isValid(http_request message);
    void handle_get_request(http_request message);
    void handle_post_request(http_request message);
};


#endif //THEQUESTS_REQUESTROUTER_H
