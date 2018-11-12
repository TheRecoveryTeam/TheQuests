//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_ABSTRACTCONTROLLER_H
#define THEQUESTS_ABSTRACTCONTROLLER_H

#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

namespace networkhelper {

    /*!
     * Dispatcher class represents the basic interface for a
     * web serivce handler.
     */
    class Controller {
    public:
        virtual void handleGet(http_request message) = 0;

        virtual void handlePost(http_request message) = 0;

//        virtual void handleHead(http_request message) = 0;
//
//        virtual void handleOptions(http_request message) = 0;
//
//        virtual void handleTrace(http_request message) = 0;
//
//        virtual void handleConnect(http_request message) = 0;
//
//        virtual void handleMerge(http_request message) = 0;
    };
}

namespace networkhelper {
    class AbstractController {
    protected:
        http_listener _listener; // main micro service network endpoint

    public:
        AbstractController();

        ~AbstractController();

        void setEndpoint(const std::string &value);

        std::string endpoint() const;

        pplx::task<void> accept();

        pplx::task<void> shutdown();

        virtual void initRestOpHandlers() {
            /* had to be implemented by the child class */
        }

        std::vector<utility::string_t> requestPath(const http_request &message);
    };
}

#endif //THEQUESTS_ABSTRACTCONTROLLER_H
