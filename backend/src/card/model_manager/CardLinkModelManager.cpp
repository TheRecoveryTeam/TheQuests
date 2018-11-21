//
// Created by Арсений Зорин on 15/11/2018.
//
#include <bsoncxx/builder/stream/document.hpp>
#include "CardLinkModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>

CardLinkModelManager::CardLinkModelManager::CardLinkModelManager() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    collection_ = (*client)["testdb"]["CardLink"];
}

std::string CardLinkModelManager::CardLinkModelManager::get(const std::string &request) {
    auto data = nlohmann::json::parse(request);
    if (data.find("id") != data.end()) {
        std::string id = data["id"];
        try {
            auto oid = bsoncxx::oid(id);
        } catch (bsoncxx::exception &exception) {
            return nlohmann::json({{"error", "Incorrect id"}}).dump();
        }
        auto query = bsoncxx::builder::stream::document{}
                << "_id" << bsoncxx::oid(id)
                << bsoncxx::builder::stream::finalize;
        bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(query.view());
        if (result) {
            return bsoncxx::to_json(*result);
        }
        return nlohmann::json({{"error", "ResourceDoesNotExist"}}).dump();
    }
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
}