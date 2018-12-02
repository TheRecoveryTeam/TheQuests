//
// Created by Арсений Зорин on 30/11/2018.
//
#include <user/model_manager/UserModelManager.h>


UserModelManager::UserModelManager::UserModelManager() : AbstractModelManager::AbstractModelManager("User") {
  session_manager_ = new SessionModelManager::SessionModelManager();
}

UserModelManager::UserModelManager::~UserModelManager() {
  delete session_manager_;
}

std::string UserModelManager::UserModelManager::login(const std::string &request) {
  std::vector<std::string> required_data = {"email", "password"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  unsigned char token[SHA256_DIGEST_LENGTH];
  std::string hash_string = "b295d117135a9763da282e7dae73a5ca7d3e5b11" + static_cast<std::string>(data["email"]) + static_cast<std::string>(data["password"]);
  SHA256((unsigned char*) hash_string.data(), hash_string.length(), (unsigned char*)&token);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << (int)token[i];
  }
  nlohmann::json query = {
      {"email", data["email"]},
      {"password", ss.str()},
  };
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()).view());
  if (result) {
    auto result_json = nlohmann::json::parse(bsoncxx::to_json(*result));
    result_json["id"] = result_json["_id"]["$oid"];
    result_json.erase("_id");
    result_json.erase("password");
    nlohmann::json new_session = {
        {"userId", result_json["id"]},
        {"email", query["email"]},
        {"password", query["password"]}
    };
    auto session = nlohmann::json::parse(session_manager_->create(new_session.dump()));
    if (session.find("error") != session.end()) {
      return session.dump();
    }
    result_json["token"] = session["token"];
    return result_json.dump();
  } else {
    return nlohmann::json({{"error", "IncorrectEmailOrPassword"}}).dump();
  }
}

std::string UserModelManager::UserModelManager::logout(const std::string &request) {
  std::vector<std::string> required_data = {"token"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query = {
      {"token", data["token"]}
  };
  return session_manager_->remove(query.dump());
}

std::string UserModelManager::UserModelManager::create(const std::string &request) {
  std::vector<std::string> required_data = {"email", "password", "nickname"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (Contains(nlohmann::json({{"email", data["email"]}}).dump())) {
    return nlohmann::json({{"error", "EmailAlreadyExist"}}).dump();
  }
  if (Contains(nlohmann::json({{"nickname", data["nickname"]}}).dump())) {
    return nlohmann::json({{"error", "NicknameAlreadyExist"}}).dump();
  }
  unsigned char token[SHA256_DIGEST_LENGTH];
  std::string hash_string = "b295d117135a9763da282e7dae73a5ca7d3e5b11" + static_cast<std::string>(data["email"]) + static_cast<std::string>(data["password"]);
  SHA256((unsigned char*) hash_string.data(), hash_string.length(), (unsigned char*)&token);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << std::hex << (int)token[i];
  }
  nlohmann::json new_user = {
      {"email", data["email"]},
      {"password", ss.str()},
      {"nickname", data["nickname"]}
  };
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_user.dump()).view()));
  if (result) {
    nlohmann::json new_session = {
        {"userId", (*result).inserted_id().get_oid().value.to_string()},
        {"email", new_user["email"]},
        {"password", new_user["password"]}
    };
    nlohmann::json session = nlohmann::json::parse(session_manager_->create(new_session.dump()));
    if (session.find("error") != session.end()) {
      return nlohmann::json({{"error", "SessionCreationError"}});
    }
    return session.dump();
  } else {
    return nlohmann::json({{"error", "UserCreationError"}}).dump();
  }
}

bool UserModelManager::UserModelManager::Contains(const std::string &request) {
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(request).view());
  if (result) {
    return true;
  } else {
    return false;
  }
}

