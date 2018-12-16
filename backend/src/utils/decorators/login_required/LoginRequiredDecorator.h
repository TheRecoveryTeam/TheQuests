//
// Created by vitaly on 15.12.18.
//

#ifndef THEQUESTS_LOGINREQUIREDDECORATOR_H
#define THEQUESTS_LOGINREQUIREDDECORATOR_H

#include <algorithm>
#include <cpprest/http_listener.h>
#include <nlohmann/json.hpp>
#include "../abstract_decorator/AbstractDecorator.h"

namespace decorators {
    class LoginRequiredDecorator : public decorators::AbstractDecorator {
    public:
        LoginRequiredDecorator(const web::http::http_request& request,
                               const std::function<void(nlohmann::json&)>& next);

        void operator()(nlohmann::json& response_args) const override;

    private:
        void replyError() const;
    };
}

#endif //THEQUESTS_LOGINREQUIREDDECORATOR_H
