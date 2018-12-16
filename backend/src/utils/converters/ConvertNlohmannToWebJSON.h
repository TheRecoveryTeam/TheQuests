//
// Created by vitaly on 15.12.18.
//

#ifndef THEQUESTS_CONVERTNLOHMANNTOWEBJSON_H
#define THEQUESTS_CONVERTNLOHMANNTOWEBJSON_H


#include <nlohmann/json.hpp>
#include <cpprest/json.h>


namespace converters {
    web::json::value ConvertNlohmannToWebJSON(const nlohmann::json& from);
}

#endif //THEQUESTS_CONVERTNLOHMANNTOWEBJSON_H
