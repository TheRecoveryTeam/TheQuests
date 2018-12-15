//
// Created by vitaly on 16.12.18.
//

#ifndef THEQUESTS_REQUIREDARGSDECORATORS_H
#define THEQUESTS_REQUIREDARGSDECORATORS_H

#include <vector>
#include <string>
#include <utils/decorators/abstract_decorator/AbstractDecorator.h>

namespace decorators {
    class RequiredArgsDecorator : public AbstractDecorator {
    public:
        RequiredArgsDecorator(const std::vector<std::string>& required_args,
                              const web::http::http_request& request,
                              const std::function<void(nlohmann::json&)>& next);

        void operator()(nlohmann::json& request_args) const override;

    private:
        std::vector<std::string> required_args;
    };
}

#endif //THEQUESTS_REQUIREDARGSDECORATORS_H
