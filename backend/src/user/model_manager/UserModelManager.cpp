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

// Login для обычных пользователей, которые зарегестрировались в приложении
std::string UserModelManager::UserModelManager::Login(const std::string &request) {
  std::vector<std::string> required_data = {"email", "password"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  // Шифруем пароль
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
  // Проверяем наличие пользователя с таким email и password в БД
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()).view());
  if (result) {
    auto result_json = nlohmann::json::parse(bsoncxx::to_json(*result));
    result_json["id"] = result_json["_id"]["$oid"];
    result_json.erase("_id");
    result_json.erase("password");
    // Создаем для пользователя новую сессию
    nlohmann::json new_session = {
        {"userId", result_json["id"]},
        {"email", query["email"]},
        {"password", query["password"]}
    };
    auto session = nlohmann::json::parse(session_manager_->Create(new_session.dump()));
    if (session.find("error") != session.end()) {
      return nlohmann::json({{"error", "SessionCreationError"}});
    }
    result_json["token"] = session["token"];
    return result_json.dump();
  } else {
    return nlohmann::json({{"error", "IncorrectEmailOrPassword"}}).dump();
  }
}

// Login для пользователей авторизовавшихся с помощью Oauth2
std::string UserModelManager::UserModelManager::LoginByOauth2(const std::string &request) {
  std::vector<std::string> required_data = {"nickname", "oauthService", "oauthId", "oauthToken"};
  std::vector<std::string> not_required_data = {"avatarPath"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query = {
      {"oauthId", data["oauthId"]}
  };
  // Проверяем наличие такого пользователя в БД
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(bsoncxx::from_json(query.dump()).view());
  nlohmann::json result_json;
  /* В случае отсутствия пользователя добавляем его в БД.
   * Иначе сохраняем данные пользователя в переменную результата */
  if (!result) {
    nlohmann::json new_user = {
        {"nickname", data["nickname"]},
        {"oauthService", data["oauthService"]},
        {"oauthId", data["oauthId"]},
        {"oauthToken", data["oauthToken"]}
    };
    DataManager::WriteNotRequiredParameters(data, new_user, not_required_data);
    result_json = nlohmann::json::parse(CreateByOauth2(new_user.dump()));
    if (result_json.find("error") != result_json.end()) {
      return result_json.dump();
    }
    query = {
        {"id", result_json["id"]}
    };
    // Получаем данные созданного пользователя
    std::vector<std::string> option = {"nickname", "avatarPath"};
    nlohmann::json result_user_data = nlohmann::json::parse(Get(query.dump(), &option));
    result_json["nickname"] = result_user_data["nickname"];
    if (result_user_data.find("avatarPath") != result_user_data.end()) {
      result_json["avatarPath"] = result_user_data["avatarPath"];
    }
  } else {
    result_json = nlohmann::json::parse(bsoncxx::to_json(*result));
    result_json["id"] = result_json["_id"]["$oid"];
    result_json.erase("_id");
    result_json.erase("oauthId");
    result_json.erase("oauthService");
    result_json.erase("oauthService");
  }
  // Создаем новую сессию для пользователя
  nlohmann::json new_session = {
      {"userId", result_json["id"]},
      {"oauthToken", data["oauthToken"]}
  };
  auto session = nlohmann::json::parse(session_manager_->CreateByOauth2(new_session.dump()));
  if (session.find("error") != session.end()) {
    return nlohmann::json({{"error", "SessionCreationError"}});
  }
  result_json["token"] = session["token"];
  return result_json.dump();
}

std::string UserModelManager::UserModelManager::Logout(const std::string &request) {
  std::vector<std::string> required_data = {"token"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json query = {
      {"token", data["token"]}
  };
  return session_manager_->Remove(query.dump());
}

std::string UserModelManager::UserModelManager::Create(const std::string &request) {
  std::vector<std::string> required_data = {"email", "password", "nickname"};
  std::vector<std::string> not_required_data = {"avatarPath"};
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
  DataManager::WriteNotRequiredParameters(data, new_user, not_required_data);
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_user.dump()).view()));
  if (result) {
    nlohmann::json new_session = {
        {"userId", (*result).inserted_id().get_oid().value.to_string()},
        {"email", new_user["email"]},
        {"password", new_user["password"]}
    };
    nlohmann::json session = nlohmann::json::parse(session_manager_->Create(new_session.dump()));
    if (session.find("error") != session.end()) {
      return nlohmann::json({{"error", "SessionCreationError"}});
    }
    session.erase("expires");
    session["id"] = session["userId"];
    session.erase("userId");
    return session.dump();
  } else {
    return nlohmann::json({{"error", "UserCreationError"}}).dump();
  }
}

std::string UserModelManager::UserModelManager::CreateByOauth2(const std::string &request) {
  std::vector<std::string> required_data = {"nickname", "oauthService", "oauthId", "oauthToken"};
  std::vector<std::string> not_required_data = {"avatarPath"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  nlohmann::json new_user = {
      {"nickname", data["nickname"]},
      {"oauthService", data["oauthService"]},
      {"oauthId", data["oauthId"]}
  };
  DataManager::WriteNotRequiredParameters(data, new_user, not_required_data);
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_user.dump()).view()));
  if (result) {
    nlohmann::json new_session = {
        {"userId", (*result).inserted_id().get_oid().value.to_string()},
        {"oauthToken", data["oauthToken"]}
    };
    nlohmann::json session = nlohmann::json::parse(session_manager_->CreateByOauth2(new_session.dump()));
    if (session.find("error") != session.end()) {
      return nlohmann::json({{"error", "SessionCreationError"}});
    }
    session.erase("expires");
    session.erase("oauthToken");
    session["id"] = session["userId"];
    session.erase("userId");
    return session.dump();
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

