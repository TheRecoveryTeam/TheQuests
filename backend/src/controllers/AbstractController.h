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
    struct RoutingEntry {
        utility::string_t url;
        web::http::method method = web::http::methods::GET;
        std::function<void(const web::http::http_request &request)> handler;
    };

    class AbstractController {
    protected:
        web::http::experimental::listener::http_listener _listener; // main micro service network endpoint

    public:
        AbstractController();

        virtual ~AbstractController();

        void setEndpoint(const std::string &value);

        std::string endpoint() const;

        pplx::task<void> accept();

        pplx::task<void> shutdown();

        virtual void initRestOpHandlers() = 0;

        static std::vector<utility::string_t> requestPath(const web::http::http_request &message);

        virtual void ConfigureRouting() = 0;

    protected:
        std::vector<RoutingEntry> _routingEntries;
    };

}

#endif //THEQUESTS_ABSTRACTCONTROLLER_H
