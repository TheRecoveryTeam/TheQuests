//
// Created by Арсений Зорин on 15/11/2018.
//
#include <bsoncxx/builder/stream/document.hpp>
#include "QuestModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>

QuestModelManager::QuestModelManager::QuestModelManager() {
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  collection_ = (*client)["testdb"]["Quest"];
}

std::string QuestModelManager::QuestModelManager::get(const std::string &request) {
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
    return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
  }
  return nlohmann::json({{"error", "NotEnoughData"}}).dump();
}

// TODO: Добавить проверку на наличие автора
std::string QuestModelManager::QuestModelManager::create(const std::string &request) {
  auto data = nlohmann::json::parse(request);
  if (data.find("title") == data.end() || data.find("description") == data.end() ||
      data.find("image") == data.end() || data.find("authorId") == data.end()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query;
  query["title"] = data["title"];
  query["description"] = data["description"];
  query["image"] = data["image"];
  std::string id = data["authorId"];
  try {
    auto oid = bsoncxx::oid(id);
  } catch (bsoncxx::exception &exception) {
    return nlohmann::json({{"error", "Incorrect authorId"}}).dump();
  }
  query["authorId"] = id;
  if (data.find("resources") != data.end()) {
    query["resources"] = data["resources"];
  }
  query["lossCardId"] = "";
  query["firstCardId"] = "";
  query["playerCount"] = 0;
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(query.dump()).view()));
  if (result) {
//    return nlohmann::json({{"_id", (*result).inserted_id().get_oid().value.to_string()}}).dump();
    return get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump());
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}