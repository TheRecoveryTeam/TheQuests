//
// Created by dpudov on 12.11.18.
//

#include <nlohmann/json.hpp>
#include "AbstractController.h"
#include "NetworkUtils.h"
#include "../../src/session/model_manager/SessionModelManager.h"

namespace networkhelper {

    AbstractController::AbstractController() = default;

    AbstractController::~AbstractController() = default;

    void AbstractController::setEndpoint(const std::string &value) {
        web::uri endpointURI(value);
        web::uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == "host_auto_ip4") {
            endpointBuilder.set_host(NetworkUtils::hostIP4());
        } else if (endpointURI.host() == "host_auto_ip6") {
            endpointBuilder.set_host(NetworkUtils::hostIP6());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        ConfigureRouting();
        _listener = web::http::experimental::listener::http_listener(endpointBuilder.to_uri());
        std::wcout << "HERE" << std::endl;

    }

    std::string AbstractController::endpoint() const {
        std::wcout << U("ADDRESS ") << AbstractController::_listener.uri().to_string().c_str() << std::endl;
        return AbstractController::_listener.uri().path();
    }

    pplx::task<void> AbstractController::accept() {
        InitHandlers();
        return _listener.open();
    }

    pplx::task<void> AbstractController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> AbstractController::requestPath(const web::http::http_request &message) {
        utility::string_t relativePath;
        relativePath = web::uri::decode(message.relative_uri().path());
        return web::uri::split_path(relativePath);
    }

    std::string AbstractController::GetCurrentUserId(const web::http::http_request& http_request, const std::string& token_type) const {
        auto token_key = GetTokenKey(http_request, token_type);
        if (token_key == "") {
            return "";
        }

        nlohmann::json request = {
                {"token", token_key}
        };

        SessionModelManager::SessionModelManager manager;
        auto response = nlohmann::json::parse(manager.GetByToken(request.dump()));

        if (response.find("error") != response.end()) {
            return "";
        }
        return response["userId"];
    }

    std::string AbstractController::GetTokenKey(const web::http::http_request& http_request, const std::string& token_type) const {
        auto headers = http_request.headers();

        std::string authentication_key = "Authorization";

        if (!headers.has(authentication_key)) {
            return "";
        }

        const auto& token_value = headers[authentication_key];

        if (token_value.length() + 1 <= token_type.length()
            || token_value.find(token_type) != 0) {
            return "";
        }

        return token_value.substr(token_type.length() + 1, token_value.length() - token_type.length() - 1);
    }

    void AbstractController::ProcessPost(const web::http::http_request& request,
                                         const AbstractController::RequestLogicProcessor& logic_processor) {

        try {
            const auto& raw_body = request.extract_json().get();

            nlohmann::json parsed_body;

            if (!raw_body.is_null()) {
                parsed_body = nlohmann::json::parse(raw_body.serialize());
            }

            logic_processor(parsed_body);
        }
        catch (...) {
            request.reply(web::http::status_codes::BadRequest);
        }
    }

    void AbstractController::ProcessGet(const web::http::http_request& request,
                                        const AbstractController::RequestLogicProcessor& logic_processor) {
        const auto& raw_query = web::uri::split_query(request.request_uri().query());

        auto parsed_query = nlohmann::json(raw_query);

        logic_processor(parsed_query);
    }

    web::http::status_code AbstractController::ValidateManagerResponse(const nlohmann::json& manager_response) const {
        if (manager_response.find("error") == manager_response.end()) {
            return web::http::status_codes::OK;
        }
        return web::http::status_codes::NotFound;
    }
}

