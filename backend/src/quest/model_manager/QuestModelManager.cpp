#include <quest/model_manager/QuestModelManager.h>


QuestModelManager::QuestModelManager::QuestModelManager() : AbstractModelManager::AbstractModelManager("Quest"){
  history_manager_ = new HistoryModelManager::HistoryModelManager();
  user_manager_ = new UserModelManager::UserModelManager();
}

QuestModelManager::QuestModelManager::~QuestModelManager() {
  delete history_manager_;
  delete user_manager_;
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
  nlohmann::json author_query = {
      {"id", quest["authorId"]}
  };
  std::vector<std::string>author_query_opts = {"nickname"};
  auto author = nlohmann::json::parse(user_manager_->Get(author_query.dump(), &author_query_opts));
  nlohmann::json result = {
    {"id", data["id"]},
    {"title", quest["title"]},
    {"description", quest["description"]},
    {"imagePath", quest["imagePath"]},
    {"currCardId", history["cardId"]},
    {"authorNickname", author["nickname"]},
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

std::string QuestModelManager::QuestModelManager::Create(const std::string &request) {
  std::vector<std::string> required_data = {"title", "description", "imagePath", "authorId"};
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
    {"imagePath", data["imagePath"]},
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

std::string QuestModelManager::QuestModelManager::List(const std::string &request) {
  std::vector<std::string> required_data = {"page", "limit"};
  std::vector<std::string> id_data = {"authorId", "userId"};
  std::vector<std::string> not_required_data = {"authorId", "userId", "asc", "stage"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query;
  if (data.find("authorId") != data.end()) {
    if (!DataManager::CheckIdCorrectness(data, std::vector<std::string>{"authorId"})) {
      return nlohmann::json({{"error", "IncorrectId"}}).dump();
    }
    query["authorId"] = {{"$oid", data["authorId"]}};
  }
  int page = data["page"];
  int limit = data["limit"];
  int start = limit * (page - 1);
  int end = limit * page;
  mongocxx::options::find opts{};
  auto options = bsoncxx::builder::stream::document{};
  options << "_id" << 1;
  opts.projection(options.view());
  if (data.find("asc") != data.end()) {
    if (data["asc"] == "true") {
      opts.sort(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("_id", 1)));
    } else if (data["asc"] == "false") {
      opts.sort(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("_id", 0)));
    }
  } else {
    opts.sort(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("_id", 1)));
  }
  auto quests_id = query.empty() ? collection_.find({}, opts)
      : collection_.find(bsoncxx::from_json(query.dump()).view(), opts);
  nlohmann::json result;
  result["quests"] = nlohmann::json::array();
  if (data.find("userId") == data.end()) {
    int i = 0;
    for (auto&& quest_id : quests_id) {
      if (i >= start && i < end) {
        auto quest_id_json = nlohmann::json::parse(bsoncxx::to_json(quest_id));
        auto quest = nlohmann::json::parse(Get(nlohmann::json({{"id", quest_id_json["_id"]["$oid"]}}).dump()));
        nlohmann::json author_query = {
            {"id", quest["authorId"]}
        };
        std::vector<std::string> author_query_opts = {"nickname"};
        auto author = nlohmann::json::parse(user_manager_->Get(author_query.dump(), &author_query_opts));
        quest["authorNickname"] = author["nickname"];
        quest.erase("authorId");
        result["quests"].push_back(quest);
      } else if (i >= end) {
        break;
      }
      ++i;
    }
  } else {
    if (data.find("stage") == data.end()) {
      int i = 0;
      for (auto&& quest_id : quests_id) {
        auto quest_id_json = nlohmann::json::parse(bsoncxx::to_json(quest_id));
        if (i >= start && i < end) {
          nlohmann::json quest_query = {
            {"id", quest_id_json["_id"]["$oid"]},
            {"userId", data["userId"]}
          };
          auto quest = nlohmann::json::parse(GetWithHistory(query.dump()));
          result["quests"].push_back(quest);
        } else if (i >= end) {
          break;
        }
        ++i;
      }
    } else {
      int i = 0;
      for (auto && quest_id : quests_id) {
        if (i >= end) {
          break;
        }
        auto quest_id_json = nlohmann::json::parse(bsoncxx::to_json(quest_id));
        nlohmann::json quest_query= {
          {"id", quest_id_json["_id"]["$oid"]},
          {"userId", data["userId"]}
        };
        auto quest = nlohmann::json::parse(GetWithHistory(query.dump()));
        if (quest["stage"] == data["stage"]) {
          if (i > start) {
            result["quests"].push_back(quest);
          }
          ++i;
        }
      }
    }
  }
  return result.dump();
}
