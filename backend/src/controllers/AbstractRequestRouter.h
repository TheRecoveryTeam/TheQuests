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
    struct RoutingEntry {
        utility::string_t url;
        web::http::method method = web::http::methods::GET;
        std::function<void(const web::http::http_request request)> handler;
    };

    class AbstractRequestRouter {
    public:
        AbstractRequestRouter();

        ~AbstractRequestRouter();

        virtual void ConfigureRouting() = 0;

        const std::vector<RoutingEntry> &GetRoutingEntries() { return _routingEntries; }

        virtual void route_get_request(web::http::http_request message) = 0;

        virtual void route_post_request(web::http::http_request message) = 0;

        bool isValid(web::http::http_request message);

    protected:
        std::vector<RoutingEntry> _routingEntries;
    };
}


#endif //THEQUESTS_REQUESTROUTER_H
