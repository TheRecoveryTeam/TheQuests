//
// Created by vitaly on 15.12.18.
//

#include <string>
#include <config/Config.h>
#include <session/model_manager/SessionModelManager.h>
#include <utils/decorators/login_required/LoginRequiredDecorator.h>

void decorators::LoginRequiredDecorator::operator()(nlohmann::json& response_args) const {
    auto headers = request.headers();

    const std::string AUTH_KEY = "Authorization";
    const std::string TOKEN_TYPE = "Bearer";

    if (!headers.has(AUTH_KEY)) {
        replyError();
        return;
    }

    const auto& token_value = headers[AUTH_KEY];

    if (token_value.length() + 1 <= TOKEN_TYPE.length()
        || token_value.find(TOKEN_TYPE) != 0) {

        replyError();
        return;
    }

    auto final_token = token_value.substr(TOKEN_TYPE.length() + 1,
                                          token_value.length() - TOKEN_TYPE.length() - 1);

    nlohmann::json requestToModelManager = {{ "token", final_token }};

    SessionModelManager::SessionModelManager manager;
    auto response = nlohmann::json::parse(manager.GetByToken(requestToModelManager.dump()));

    if (response.find("error") != response.end()) {
        replyError();
        return;
    }

    response_args[config::fields::USER_ID] = response[config::fields::USER_ID];
    response_args[config::fields::TOKEN] = final_token;

    next(response_args);
}

void decorators::LoginRequiredDecorator::replyError() const {
    request.reply(web::http::status_codes::Unauthorized);
}

decorators::LoginRequiredDecorator::LoginRequiredDecorator(const web::http::http_request& request,
                                                           const std::function<void(nlohmann::json&)>& next)
: AbstractDecorator(request, next) { }
