//
// Created by vitaly on 15.12.18.
//

#include <utils/decorators/abstract_decorator/AbstractDecorator.h>


decorators::AbstractDecorator::AbstractDecorator(const web::http::http_request& request,
                                                 const std::function<void(nlohmann::json&)>& next) :
    request(request),
    next(next)
{ }

void decorators::AbstractDecorator::operator()(nlohmann::json& response_args) const {
    next(response_args);
}
