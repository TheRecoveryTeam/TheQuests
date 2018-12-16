//
// Created by vitaly on 16.12.18.
//

#include <utils/converters/ConvertNlohmannToWebJSON.h>


web::json::value converters::ConvertNlohmannToWebJSON(const nlohmann::json& from) {
    return web::json::value::parse(from.dump());
}
