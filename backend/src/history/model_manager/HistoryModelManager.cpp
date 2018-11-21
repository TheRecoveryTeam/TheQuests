//
// Created by Арсений Зорин on 15/11/2018.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "HistoryModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>

HistoryModelManager::HistoryModelManager::HistoryModelManager() {
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  collection_ = (*client)["testdb"]["History"];
  quest_manager_ = new QuestModelManager::QuestModelManager();
}

// TODO: Добавить проверку существования юзера
std::string HistoryModelManager::HistoryModelManager::get(const std::string &request) {
  auto data = nlohmann::json::parse(request);
  if (data.find("userId") == data.end() || data.find("questId") == data.end()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  std::string quest_id = data["questId"];
  std::string user_id = data["userId"];
  try {
    auto quest_oid = bsoncxx::oid(quest_id);
    auto user_oid = bsoncxx::oid(user_id);
  } catch (bsoncxx::exception &exception) {
    return nlohmann::json({{"error", "Incorrect id"}}).dump();
  }
  auto quest = nlohmann::json::parse(quest_manager_->get(nlohmann::json({{"id", quest_id}}).dump()));
//  auto user = nlohmann::json::parse(user_manager_.get(nlohmann::json({{"id", user_id}})));
  if (quest.find("error") != quest.end()) {
    return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
  }
  auto query = bsoncxx::builder::stream::document{}
      << "questId" << quest_id
      << "userId" << user_id
      << bsoncxx::builder::stream::finalize;
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(query.view());
  if (result) {
    auto json_result = nlohmann::json::parse(bsoncxx::to_json(*result));
    json_result["id"] = json_result["_id"]["$oid"];
    json_result.erase("_id");
    return json_result.dump();
  }
  return nlohmann::json({{"warning", "DoesNotExist"}}).dump();
}

// TODO: Добавить проверку на существование юзера
std::string HistoryModelManager::HistoryModelManager::create(const std::string &request) {
  auto data = nlohmann::json::parse(request);
  if (data.find("questId") == data.end() || data.find("userId") == data.end()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  std::string quest_id = data["questId"];
  std::string user_id = data["userId"];
  try {
    auto quest_oid = bsoncxx::oid(quest_id);
    auto user_oid = bsoncxx::oid(user_id);
  } catch (bsoncxx::exception &exception) {
    return nlohmann::json({{"error", "Incorrect id"}}).dump();
  }
  auto quest = nlohmann::json::parse(quest_manager_->get(nlohmann::json({{"id", quest_id}}).dump()));
  if (quest.find("error") != quest.end()) {
    return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
  }
  auto history_received = nlohmann::json::parse(get(nlohmann::json({
                                                                       {"questId", quest_id},
                                                                       {"userId", user_id}
                                                                   }).dump()));
  if (history_received.find("warning") == history_received.end()) {
    return nlohmann::json({{"error", "HistoryAlreadyExist"}}).dump();
  }
  nlohmann::json query;
  query["questId"] = quest_id;
  query["userId"] = user_id;
  query["stage"] = "process";
  query["cardId"] = quest["firstCardId"];
//  for (auto resource : quest["resources"]) {
////    query["resources"].push_back({{resource, 50}});
////  }
  for (auto &resource : quest["resources"].get<std::vector<std::string>>()) {
    query["resources"][resource] = 50;
  }
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(query.dump()).view()));
  if (result) {
    nlohmann::json json_result = nlohmann::json::parse(get(nlohmann::json({
                                                                              {"questId", quest_id},
                                                                              {"userId", user_id}
                                                                          }).dump()));
    return json_result.dump();
  }
  return nlohmann::json({{"error", "CreationError"}}).dump();
}

std::string HistoryModelManager::HistoryModelManager::update(const std::string &request) {
  auto data = nlohmann::json::parse(request);
  if (data.find("id") == data.end() || data.find("cardId") == data.end()) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query;
  query["$set"]["cardId"] = data["cardId"];
  if (data.find("stage") != data.end()) {
    query["$set"]["stage"] = data["stage"];
  }
  for (auto &resource : data["resources"].get<std::map<std::string, int>>()) {
    query["$set"]["resources"][resource.first] = resource.second;
  }
//  for (auto& resource : data["resources"].get<std::map<std::string, int>>()) {
//    query["$set"]["resources"][resource.first] = resource.second;
//  }
  bsoncxx::stdx::optional<mongocxx::result::update> result = collection_.update_one(bsoncxx::builder::stream::document{}
                                                                                        << "_id"
                                                                                        << bsoncxx::oid(data["id"])
                                                                                        << bsoncxx::builder::stream::finalize,
                                                                                    bsoncxx::from_json(query.dump()).view());
  if (!result) {
    return nlohmann::json({{"error", "UpdateError"}}).dump();
  }
//  return nlohmann::json({{"id", (*result).upserted_id().value().get_oid().value.to_string()}}).dump();
  return nlohmann::json().dump();
}