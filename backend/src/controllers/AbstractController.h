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

    public:
        typedef std::function<std::pair<web::http::status_code, web::json::value>(const nlohmann::json& requestArgs)> requestLogicProcessor;

        AbstractController();

        virtual ~AbstractController();

        void setEndpoint(const std::string &value);

        std::string endpoint() const;

        pplx::task<void> accept();

        pplx::task<void> shutdown();

        virtual void InitHandlers() = 0;

        static std::vector<utility::string_t> requestPath(const web::http::http_request &message);

        virtual void ConfigureRouting() = 0;

    protected:
        web::http::experimental::listener::http_listener _listener; // main micro service network endpoint
        std::vector<RoutingEntry> _routingEntries;

        // returns empty string in the case of failure
        std::string GetCurrentUserId(const web::http::http_request& http_request, const std::string& token_type) const;

        void ProcessPost(const web::http::http_request& request, const requestLogicProcessor& logicProcessor);
        void ProcessGet(const web::http::http_request& request, const requestLogicProcessor& logicProcessor);
        web::http::status_code ValidateManagerResponse(const nlohmann::json& manager_response) const;

    private:
        std::string GetTokenKey(const web::http::http_request&, const std::string& token_type) const;
    };
}

#endif //THEQUESTS_ABSTRACTCONTROLLER_H
