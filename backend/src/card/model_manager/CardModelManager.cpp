//
// Created by Арсений Зорин on 10/11/2018.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "CardModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>


CardModelManager::CardModelManager::CardModelManager() {
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  collection_ = (*client)["testdb"]["card"];
}


std::string CardModelManager::CardModelManager::get(const std::string& request) {
  auto data = nlohmann::json::parse(request);
  if (data.find("id") != data.end()) {
    std::string id = data["id"];
    try {
      auto oid = bsoncxx::oid(id);
    } catch(bsoncxx::exception& exception) {
      return nlohmann::json({{"error", "Incorrect id"}}).dump();
    }
    auto query = bsoncxx::builder::stream::document{}
        << "_id" << bsoncxx::oid(id)
        << bsoncxx::builder::stream::finalize;
    bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(query.view());
    if (result) {
      return bsoncxx::to_json(*result);
    }
    return nlohmann::json({{"error", "CardDoesNotExist"}}).dump();
  }
  return nlohmann::json({{"error", "NotEnoughData"}}).dump();
}


std::string CardModelManager::CardModelManager::create(const std::string& request) {
  nlohmann::json data;
  if (data.find("questId") == data.end() || data.find("title") == data.end() || data.find("type") == data.end()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query;
  query["questId"] = data["questId"];
  query["title"] = data["title"];
  query["type"] = data["type"];
  if (data.find("imagePath") != data.end()) {
    query["imagePath"] = data["imagePath"];
  }
  if (data.find("description") != data.end()) {
    query["description"] = data["description"];
  }
  if (data.find("links") != data.end()) {
    query["links"] = data["links"];
  }
  bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection_.insert_one((bsoncxx::from_json(query.dump()).view()));
  if (result) {
    return nlohmann::json({{"_id", (*result).inserted_id().get_oid().value.to_string()}}).dump();
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}