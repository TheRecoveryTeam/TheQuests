#include <session/model_manager/SessionModelManager.h>


std::string SessionModelManager::SessionModelManager::Get(const std::string &request,
                                                          const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::Get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"userId"};
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}

std::string SessionModelManager::SessionModelManager::GetByToken(const std::string &request) {
  std::vector<std::string> required_data = {"token"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query = {
      {"token", data["token"]}
  };
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()).view());
  if (result) {
    auto result_json = nlohmann::json::parse(bsoncxx::to_json(*result));
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() > result_json["expires"]) {
      this->Remove(query.dump());
      return nlohmann::json({{"error", "TokenHasExpired"}}).dump();
    }
    result_json["id"] = result_json["_id"]["$oid"];
    result_json.erase("_id");
    std::vector<std::string> id_data = {"userId"};
    DataManager::UnpackOid(result_json, id_data);
    return result_json.dump();
  } else {
    return nlohmann::json({{"error", "ObjectDoesNotExist"}}).dump();
  }
}

std::string SessionModelManager::SessionModelManager::Create(const std::string &request) {
  std::vector<std::string> required_data = {"userId", "email", "password"};
  std::vector<std::string> id_data = {"userId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  unsigned char token[SHA256_DIGEST_LENGTH];
  std::string hash_string = "b295d117135a9763da282e7dae73a5ca7d3e5b11" + static_cast<std::string>(data["email"]) + static_cast<std::string>(data["password"]) +
      std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
  SHA256((unsigned char*) hash_string.data(), hash_string.length(), (unsigned char*) &token);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << (int)token[i];
  }
  nlohmann::json new_session = {
      {"userId", {{"$oid", data["userId"]}}},
      {"token", ss.str()},
      {"expires",   std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count() + 86400}
  };
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_session.dump()).view()));
  if (result) {
    std::vector<std::string> options = {"userId", "token"};
    return this->Get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump(), &options);
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}

std::string SessionModelManager::SessionModelManager::CreateByOauth2(const std::string &request) {
  std::vector<std::string> required_data = {"oauthToken", "userId"};
  std::vector<std::string> id_data = {"userId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  unsigned char token[SHA256_DIGEST_LENGTH];
  std::string hash_string = "b295d117135a9763da282e7dae73a5ca7d3e5b11" + static_cast<std::string>(data["oauthToken"]) +
      std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
  SHA256((unsigned char*) hash_string.data(), hash_string.length(), (unsigned char*) &token);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << (int)token[i];
  }
  nlohmann::json new_session = {
      {"userId", {{"$oid", data["userId"]}}},
      {"token", ss.str()},
      {"expires",   std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch()).count() + 43000}
  };
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_session.dump()).view()));
  if (result) {
    std::vector<std::string> options = {"userId", "token"};
    return this->Get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump(), &options);
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}

std::string SessionModelManager::SessionModelManager::Remove(const std::string &request) {
  std::vector<std::string> required_data = {"token"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query = {
      {"token", data["token"]}
  };
  bsoncxx::stdx::optional<mongocxx::result::delete_result> result = collection_.delete_one(bsoncxx::from_json(query.dump()));
  if (result) {
    return nlohmann::json().dump();
  } else {
    return nlohmann::json({{"error", "SessionDeleteError"}}).dump();
  }
}