//
// Created by vitaly on 16.12.18.
//

#include "RequiredArgsDecorator.h"

decorators::RequiredArgsDecorator::RequiredArgsDecorator(const std::vector<std::string>& required_args,
                                                         const web::http::http_request& request,
                                                         const std::function<void(nlohmann::json&)>& next):
    AbstractDecorator(request, next),
    required_args(required_args)
{ }

void decorators::RequiredArgsDecorator::operator()(nlohmann::json& request_args) const {
    for (auto& arg : required_args) {
        if (request_args.find(arg) == request_args.end()) {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }
    }

    next(request_args);
}
