//
// Created by dpudov on 09.11.18.
//

#ifndef THEQUESTS_NETWORKHELPER_H
#define THEQUESTS_NETWORKHELPER_H

#include <cpprest/http_listener.h>

namespace networkhelper {

    class BaseController {
        virtual void onException(const web::http::http_request &request, const std::exception &exception) {}
    };

    struct RoutingEntry {
        utility::string_t url;
        web::http::method method = web::http::methods::GET;
        std::function<void(const web::http::http_request &request)> handler;
    };

    class BaseServer {
    public:
        virtual void ConfigureRouting() {}

        pplx::task<void> Start(const utility::string_t &endpoint) {
            using namespace web;
            using namespace web::http;
            using namespace web::http::experimental::listener;

            ConfigureRouting();

            _listener = http_listener(uri(endpoint));
            _listener.support([this](const http_request &request) {
                bool found = false;
                for (auto &entry : _routingEntries) {
                    if (request.relative_uri().path() != entry.url || request.method() != entry.method) {
                        continue;
                    }
                    entry.handler(request);
                    found = true;
                    break;
                }
                if (!found) {
                    request.reply(status_codes::NotFound);
                }
            });

            return _listener.open();
        }

        pplx::task<void> Stop() { return _listener.close(); }

        const std::vector<RoutingEntry> &GetRoutingEntries() { return _routingEntries; }

        utility::string_t GetEndpoint() { return _listener.uri().to_string(); }

    protected:
        web::http::experimental::listener::http_listener _listener;
        std::vector<RoutingEntry> _routingEntries;
    };
}

#endif //THEQUESTS_NETWORKHELPER_H
