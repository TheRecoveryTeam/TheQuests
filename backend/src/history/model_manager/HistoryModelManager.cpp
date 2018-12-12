//
// Created by Арсений Зорин on 15/11/2018.
//

#include <bsoncxx/builder/stream/document.hpp>
#include <history/model_manager/HistoryModelManager.h>
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>


std::string HistoryModelManager::HistoryModelManager::Get(const std::string &request,
                                                          const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::Get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"userId", "questId", "cardId"};
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}
// TODO: Добавить проверку существования юзера
//std::string HistoryModelManager::HistoryModelManager::GetUserHistory(const std::string &request) {
//  std::vector<std::string> required_data = {"userId", "questId", "firstCardId", "resources"};
//  std::vector<std::string> required_id = {"userId", "questId", "firstCardId"};
//  auto data = nlohmann::json::parse(request);
//  if (!DataManager::CheckRequiredParameters(data, required_data)) {
//    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
//  }
//  if (!DataManager::CheckIdCorrectness(data, required_id)) {
//    return nlohmann::json({{"error", "IncorrectId"}}).dump();
//  }
//  nlohmann::json query = {
//      {"questId", {{"$oid", data["questId"]}}},
//      {"userId", {{"$oid", data["userId"]}}}
//  };
//  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()));
//  if (result) {
//    std::vector<std::string> id_data = {"questId", "userId", "cardId"};
//    auto json_result = nlohmann::json::parse(bsoncxx::to_json(*result));
//    DataManager::UnpackOid(json_result, id_data);
//    json_result["id"] = json_result["_id"]["$oid"];
//    json_result.erase("_id");
//
//    return json_result.dump();
//  } else {
//    auto new_history = nlohmann::json::parse(Create(nlohmann::json({{"userId", data["userId"]},
//                                                                    {"questId", data["questId"]},
//                                                                    {"firstCardId", data["firstCardId"]},
//                                                                    {"resources", data["resources"]}}).dump()));
//    return new_history.dump();
//  }
//}

std::string HistoryModelManager::HistoryModelManager::GetUserHistory(const std::string &request) {
  std::vector<std::string> required_data = {"userId", "questId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, required_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  nlohmann::json query = {
      {"questId", {{"$oid", data["questId"]}}},
      {"userId", {{"$oid", data["userId"]}}}
  };
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()));
  if (result) {
    std::vector<std::string> id_data = {"questId", "userId", "cardId"};
    auto json_result = nlohmann::json::parse(bsoncxx::to_json(*result));
    DataManager::UnpackOid(json_result, id_data);
    json_result["id"] = json_result["_id"]["$oid"];
    json_result.erase("_id");
    return json_result.dump();
  } else {
    return nlohmann::json({{"warning", "HistoryDoesNotExist"}}).dump();
  }
}

std::string HistoryModelManager::HistoryModelManager::Create(const std::string &request) {
  std::vector<std::string> required_data = {"userId", "questId", "firstCardId", "resources"};
  std::vector<std::string> required_id = {"userId", "questId", "firstCardId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, required_id)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }

//  auto quest = nlohmann::json::parse(quest_manager_->Get(nlohmann::json({{"id", data["questId"]}}).dump()));
////  auto user = nlohmann::json::parse(user_manager_.get(nlohmann::json({{"id", user_id}})));
//  if (quest.find("error") != quest.end()) {
//    return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
//  }

//  auto history_received = nlohmann::json::parse(get_user_history(nlohmann::json({
//    {"questId", data["questId"]},
//    {"userId", data["userId"]}
//  }).dump()));
//  if (history_received.find("warning") == history_received.end()) {
//    return nlohmann::json({{"error", "HistoryAlreadyExist"}}).dump();
//  }
  nlohmann::json query = {
      {"questId", {{"$oid", data["questId"]}}},
      {"userId", {{"$oid", data["userId"]}}},
      {"stage", "process"},
      {"cardId", {{"$oid", data["firstCardId"]}}}
  };
  for (auto &resource : data["resources"].get<std::vector<std::string>>()) {
    query["resources"][resource] = 50;
  }
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(query.dump())));
  if (result) {
    auto json_result = nlohmann::json::parse(GetUserHistory(nlohmann::json({
                                                                               {"questId", data["questId"]},
                                                                               {"userId", data["userId"]},
                                                                               {"firstCardId", data["firstCardId"]},
                                                                               {"resources", data["resources"]}
                                                                           }).dump()));
    return json_result.dump();
  }
  return nlohmann::json({{"error", "CreationError"}}).dump();
}

//// TODO: Добавить проверку на существование юзера
std::string HistoryModelManager::HistoryModelManager::Update(const std::string &request) {
  std::vector<std::string> required_data = {"id", "cardId"};
  std::vector<std::string> id_data = {"id", "cardId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  nlohmann::json update;
  update["$set"]["cardId"]["$oid"] = data["cardId"];
  if (data.find("stage") != data.end()) {
    update["$set"]["stage"] = data["stage"];
  }
  for (auto &resource : data["resources"].get<std::map<std::string, int>>()) {
    update["$set"]["resources"][resource.first] = resource.second;
  }
  nlohmann::json query = {
    {"_id", {{"$oid", data["id"]}}}
  };
  bsoncxx::stdx::optional<mongocxx::result::update> update_result = collection_.update_one(
    bsoncxx::from_json(query.dump()),
    bsoncxx::from_json(update.dump())
  );
  if (!update_result) {
    return nlohmann::json({{"error", "UpdateError"}}).dump();
  }
  return Get(nlohmann::json({{"id", data["id"]}}).dump());
}