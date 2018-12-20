//
// Created by vitaly on 16.12.18.
//

#include <utils/converters/ConvertNlohmannToWebJSON.h>


std::string converters::ConvertNlohmannToWebJSON(const nlohmann::json& from) {
    return from.dump();
}
