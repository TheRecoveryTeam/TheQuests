//
// Created by Арсений Зорин on 27/11/2018.
//
#include <core/model_manager/ModelManager.h>


AbstractModelManager::AbstractModelManager::AbstractModelManager(const std::string &collection_name) {
  collection_name_ = collection_name;
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  collection_ = (*client)["testdb"][collection_name_];
}

std::string AbstractModelManager::AbstractModelManager::Get(const std::string &request,
                                                            const std::vector<std::string> *projection) {
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, std::vector<std::string>{"id"})) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, std::vector<std::string>{"id"})) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  auto query = bsoncxx::builder::stream::document{}
      << "_id" << bsoncxx::oid(data["id"])
      << bsoncxx::builder::stream::finalize;
  bsoncxx::stdx::optional<bsoncxx::document::value> result;
  if (projection && !projection->empty()) {
    mongocxx::options::find opts{};
    auto options = bsoncxx::builder::stream::document{};
    for (const auto& key : *projection) {
      options << key << 1;
    }
    opts.projection(options.view());
    result = collection_.find_one(query.view(), opts);
  } else {
    result = collection_.find_one(query.view());
  }
  if (result) {
    auto result_json = nlohmann::json::parse(bsoncxx::to_json(*result));
    result_json["id"] = result_json["_id"]["$oid"];
    result_json.erase("_id");
    return result_json.dump();
  } else {
    return nlohmann::json({{"error", "ObjectDoesNotExist"}}).dump();
  }
}
