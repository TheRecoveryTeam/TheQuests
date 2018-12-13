#include <quest/model_manager/QuestModelManager.h>


QuestModelManager::QuestModelManager::QuestModelManager() : AbstractModelManager::AbstractModelManager("Quest"){
  history_manager_ = new HistoryModelManager::HistoryModelManager();
}

QuestModelManager::QuestModelManager::~QuestModelManager() {
  delete history_manager_;
}

std::string QuestModelManager::QuestModelManager::Get(const std::string &request,
                                                      const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::Get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"authorId", "firstCardId", "lossCardId"};
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}

std::string QuestModelManager::QuestModelManager::GetWithHistory(const std::string &request) {
  std::vector<std::string> required_data = {"id", "userId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json quest_query = {
    {"id", data["id"]}
  };
  auto quest = nlohmann::json::parse(Get(quest_query.dump()));
  if (quest.find("error") != quest.end()) {
    return quest.dump();
  }
  nlohmann::json history_query = {
    {"questId", data["id"]},
    {"userId", data["userId"]}
  };
  auto history = nlohmann::json::parse(history_manager_->GetUserHistory(history_query.dump()));
  if (history.find("error") == history.end()) {
    return history.dump();
  }
  if (history.find("warning") == history.end()) {
    nlohmann::json new_history = {
      {"questId", data["id"]},
      {"userId", data["userId"]},
      {"firstCardId", quest["firstCardId"]},
      {"resources", quest["resources"]}
    };
    history = nlohmann::json::parse(history_manager_->Create(new_history.dump()));
    if (history.find("error") != history.end()) {
      return history.dump();
    }
  }
  nlohmann::json result = {
    {"id", data["id"]},
    {"title", quest["title"]},
    {"description", quest["description"]},
    {"imagePath", quest["imagePath"]},
    {"currCardId", history["cardId"]},
    {"authorNickname", quest["authorId"]},
    {"playerCount", quest["playerCount"]},
    {"stage", history["stage"]},
  };
  auto resources_array =nlohmann::json();
  for (auto &resource: history["resources"].get<std::map<std::string, int>>()) {
    resources_array.push_back({
      {"name", resource.first},
      {"value", resource.second}
    });
  }
  result["resources"] = resources_array;
  return result.dump();
}

// TODO: Добавить проверку на наличие автора
std::string QuestModelManager::QuestModelManager::Create(const std::string &request) {
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
    {"playerCount", 0}
  };
  DataManager::WriteNotRequiredParameters(data, new_quest, not_required_data);
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
    result = collection_.insert_one((bsoncxx::from_json(new_quest.dump()).view()));
  if (result) {
    return this->Get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump());
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}