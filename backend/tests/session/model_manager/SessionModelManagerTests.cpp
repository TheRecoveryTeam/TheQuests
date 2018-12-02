//
// Created by Арсений Зорин on 30/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <session/model_manager/SessionModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>
#include <openssl/sha.h>
#include <sstream>

class SessionModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["Session"];
    session_manager = new SessionModelManager::SessionModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> sessions;
    unsigned char token_char[SHA256_DIGEST_LENGTH];
    std::string hash_string = (std::string)"token" + (std::string)"b295d117135a9763da282e7dae73a5ca7d3e5b11";

    SHA256((unsigned char*) hash_string.data(), (hash_string).length(), (unsigned char*) &token_char);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
      ss << std::hex << (int)token_char[i];
    }
    sessions.push_back(nlohmann::json({
                                        {"userId", {{"$oid", bsoncxx::oid().to_string()}}},
                                        {"token", ss.str()},
                                        {"expires", std::chrono::duration_cast<std::chrono::seconds>(
                                            std::chrono::system_clock::now().time_since_epoch()).count() + 86400}
                                    }));
    for (const auto &session : sessions) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(session.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
  }

  std::vector<std::string> *id_list;
  SessionModelManager::SessionModelManager *session_manager;
};

TEST_F(SessionModelManagerTests, getSessionWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_session = nlohmann::json::parse(session_manager->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_session["id"]) << "Wrong session received";
}

TEST_F(SessionModelManagerTests, getSessionWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_session = nlohmann::json::parse(session_manager->get(query.dump()));
  ASSERT_TRUE(received_session.find("error") != received_session.end())
                << "Doesn't return error on incorrect quest id";
}

TEST_F(SessionModelManagerTests, getSessionByToken) {
  std::string token = nlohmann::json::parse(session_manager->get(nlohmann::json{{"id", (*id_list)[0]}}.dump()))["token"];
  nlohmann::json query = {
      {"token", token}
  };
  nlohmann::json result = nlohmann::json::parse(session_manager->get_by_token(query.dump()));
  ASSERT_EQ(token, result["token"]) << "Wrong session received";
}

TEST_F(SessionModelManagerTests, getSessionByExpiredToken) {
  nlohmann::json session = {
      {"userId", bsoncxx::oid().to_string()},
      {"token", "123"},
      {"expires", 15}
  };
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  auto collection = (*client)["testdb"]["Session"];
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection.insert_one((bsoncxx::from_json(session.dump()).view()));
  auto received_session = nlohmann::json::parse(session_manager->get_by_token(nlohmann::json({{"token", session["token"]}}).dump()));
  ASSERT_TRUE(received_session.find("error") != received_session.end() && received_session["error"] == "TokenHasExpired")
    << "Doesn't return error on expired token";
}

TEST_F(SessionModelManagerTests, getSessionWithoutId) {
  nlohmann::json query = {};
  auto received_session = nlohmann::json::parse(session_manager->get(query.dump()));
  ASSERT_TRUE(received_session.find("error") != received_session.end()) << "Doesn't return error on incorrect data";
}

TEST_F(SessionModelManagerTests, addCorrectSession) {
  nlohmann::json data = {
      {"userId", bsoncxx::oid().to_string()},
      {"email", "test@mail.ru"},
      {"password", "123456"}
  };
  auto result = nlohmann::json::parse(session_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") == result.end()) << "The session has't been correctly added to the database";
  ASSERT_TRUE(result["userId"] == data["userId"]) << "The session added with incorrect user id";
}

TEST_F(SessionModelManagerTests, removeExistingSession) {
  nlohmann::json session = {
      {"userId", bsoncxx::oid().to_string()},
      {"token", "1234"},
      {"expires", 15}
  };
  auto client = MongoAccess::MongoAccess::instance().get_connection();
  auto collection = (*client)["testdb"]["Session"];
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection.insert_one((bsoncxx::from_json(session.dump()).view()));
  nlohmann::json query = {
      {"token", session["token"]}
  };
  auto remove_result = nlohmann::json::parse(session_manager->remove(query.dump()));
  ASSERT_TRUE(remove_result.find("error") == remove_result.end())
    << "Doesn't correctly remove session";
  auto received_session = nlohmann::json::parse(session_manager->get_by_token(query.dump()));
  ASSERT_TRUE(received_session.find("error") != received_session.end() && received_session["error"] == "ObjectDoesNotExist")
    << "Doesn't remove session";
}

TEST_F(SessionModelManagerTests, removeNotExistingSession) {
  nlohmann::json query = {
      {"token", "NotExistingToken"}
  };
  auto remove_result = nlohmann::json::parse(session_manager->remove(query.dump()));
  ASSERT_TRUE(remove_result.find("error") == remove_result.end())
                << "Doesn't correctly working with not existing token";
}
