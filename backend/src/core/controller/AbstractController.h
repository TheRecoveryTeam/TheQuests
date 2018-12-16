//
// Created by dpudov on 08.11.18.
//

#ifndef THEQUESTS_ABSTRACTCONTROLLER_H
#define THEQUESTS_ABSTRACTCONTROLLER_H

#include <string>
#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <functional>
#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>

namespace networkhelper {
    struct RoutingEntry {
        utility::string_t url;
        web::http::method method = web::http::methods::GET;
        std::function<void(const web::http::http_request &request)> handler;
    };

    class AbstractController {

    public:
        typedef std::function<void(nlohmann::json& request_args)> RequestLogicProcessor;

        AbstractController();

        virtual ~AbstractController();

        void SetEndpoint(const std::string &value);

        std::string Endpoint() const;

        pplx::task<void> Accept();

        pplx::task<void> Shutdown();

        virtual void InitHandlers() = 0;

        static std::vector<utility::string_t> RequestPath(const web::http::http_request &message);

        virtual void ConfigureRouting() = 0;

    protected:
        web::http::experimental::listener::http_listener _listener; // main micro service network endpoint
        std::vector<RoutingEntry> _routingEntries;

        // returns empty string in the case of failure
        std::string GetCurrentUserId(const web::http::http_request& http_request, const std::string& token_type) const;

        void ProcessPost(const web::http::http_request& request, const RequestLogicProcessor& logic_processor);
        void ProcessGet(const web::http::http_request& request, const RequestLogicProcessor& logic_processor);
        web::http::status_code ValidateManagerResponse(const nlohmann::json& manager_response) const;

    private:
        std::string GetTokenKey(const web::http::http_request&, const std::string& token_type) const;
    };
}

#endif //THEQUESTS_ABSTRACTCONTROLLER_H
