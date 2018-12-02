//
// Created by Арсений Зорин on 15/11/2018.
//
#include <quest/model_manager/QuestModelManager.h>


std::string QuestModelManager::QuestModelManager::get(const std::string &request, const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"authorId", "firstCardId", "lossCardId"};
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}

// TODO: Добавить проверку на наличие автора
std::string QuestModelManager::QuestModelManager::create(const std::string &request) {
  std::vector<std::string> required_data = {"title", "description", "image", "authorId"};
  std::vector<std::string> id_data = {"authorId"};
  std::vector<std::string> not_required_data = {"resources"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  nlohmann::json new_quest = {
      {"title", data["title"]},
      {"description", data["description"]},
      {"image", data["image"]},
      {"authorId", {{"$oid", data["authorId"]}}},
      {"playerCount", 0},
  };
  DataManager::WriteNotRequiredParameters(data, new_quest, not_required_data);
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
    result = collection_.insert_one((bsoncxx::from_json(new_quest.dump()).view()));
  if (result) {
    return this->get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump());
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}