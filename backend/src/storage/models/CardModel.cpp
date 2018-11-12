//
// Created by Арсений Зорин on 10/11/2018.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "CardModel.h"
#include <mongocxx/client.hpp>
#include <connections/Connection_singleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>


CardModel::CardModel::CardModel(const std::string& json) {
  nlohmann::json data = nlohmann::json::parse(json);
  id_ = data.find("_id") != data.end() ? data["_id"] : "";
  quest_id_ = data.find("questId") != data.end() ? data["questId"] : "";
  title_ = data.find("title") != data.end() ? data["title"] : "";
  image_path_ = data.find("imagePath") != data.end() ? data["imagePath"] : "";
  description_ = data.find("description") != data.end() ? data["description"] : "";
  type_ = data.find("type") != data.end() ? data["type"] : "";
  if (data.find("links") != data.end()) {
    links_ = data["links"].get<std::map<std::string, std::string>>();
  }
  if (data.find("type") != data.end()) {
    std::string type_value = data["type"];
    if (type_value == "choose" || type_value == "input" || type_value == "finish") {
      type_ = type_value;
      return;
    }
  }
  type_ = "";
}


std::string CardModel::CardModel::get() {
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  auto collection = (*client)["testdb"]["card"];
  if (!id_.empty()) {
    try {
      auto id = bsoncxx::oid(id_);
    } catch(bsoncxx::exception& exception) {
      return nlohmann::json({{"error", "Incorrect id"}}).dump();
    }
    auto query_parameter = bsoncxx::builder::stream::document{}
        << "_id" << bsoncxx::oid(id_)
        << bsoncxx::builder::stream::finalize;
    bsoncxx::stdx::optional<bsoncxx::document::value> result = collection.find_one(query_parameter.view());
    if (result) {
      return bsoncxx::to_json(*result);
    }
    return nlohmann::json({{"error", "CardDoesNotExist"}}).dump();
  }
  return nlohmann::json({{"error", "NotEnoughData"}}).dump();
}


std::string CardModel::CardModel::create() {
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  auto collection = (*client)["testdb"]["card"];
  nlohmann::json data;
  if (quest_id_.empty() || title_.empty() || type_.empty()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  data["questId"] = quest_id_;
  data["title"] = title_;
  data["type"] = type_;
  if (!image_path_.empty()) {
    data["imagePath"] = image_path_;
  }
  if (!description_.empty()) {
    data["description"] = description_;
  }
  if (!links_.empty()) {
    data["links"] = nlohmann::json(links_);
  }
  bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one((bsoncxx::from_json(data.dump()).view()));
  if (result) {
    return nlohmann::json({{"_id", (*result).inserted_id().get_oid().value.to_string()}}).dump();
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}