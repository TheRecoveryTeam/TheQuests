//
// Created by vitaly on 15.12.18.
//

#ifndef THEQUESTS_ABSTRACTDECORATOR_H
#define THEQUESTS_ABSTRACTDECORATOR_H

#include <algorithm>
#include <cpprest/http_listener.h>
#include <nlohmann/json.hpp>

namespace decorators {
    class AbstractDecorator {
    public:
        AbstractDecorator() = delete;
        AbstractDecorator(const web::http::http_request& request,
                          const std::function<void(nlohmann::json&)>& next);

        virtual ~AbstractDecorator() = default;

        virtual void operator()(nlohmann::json& response_args) const;

    protected:
        const web::http::http_request& request;
        const std::function<void(nlohmann::json&)>& next;
    };
}

#endif //THEQUESTS_ABSTRACTDECORATOR_H
