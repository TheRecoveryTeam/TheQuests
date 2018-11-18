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

namespace networkhelper {

    /*!
     * Dispatcher class represents the basic interface for a
     * web serivce handler.
     */
    class Controller {
    public:
        virtual void handleGet(web::http::http_request message) = 0;

        virtual void handlePost(web::http::http_request message) = 0;
    };
}

namespace networkhelper {
    class AbstractController {
    protected:
        web::http::experimental::listener::http_listener _listener; // main micro service network endpoint

    public:
        AbstractController();

        ~AbstractController();

        void setEndpoint(const std::string &value);

        std::string endpoint() const;

        pplx::task<void> accept();

        pplx::task<void> shutdown();

        virtual void initRestOpHandlers() = 0;

        std::vector<utility::string_t> requestPath(const web::http::http_request &message);
    };
}

#endif //THEQUESTS_ABSTRACTCONTROLLER_H
