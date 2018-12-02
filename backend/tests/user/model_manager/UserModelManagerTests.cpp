//
// Created by Арсений Зорин on 30/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <user/model_manager/UserModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

class UserModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["User"];
    user_manager = new UserModelManager::UserModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> users;
    users.push_back(nlohmann::json({
                                          {"email", "test@bk.ru"},
                                          {"password", "123456"},
                                          {"nickname", "testuser"}
                                      }));
    users.push_back(nlohmann::json({
                                       {"email", "test@bk.ru"},
                                       {"password", "12345555"},
                                       {"nickname", "testuser"}
                                   }));
    for (const auto &user : users) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(user.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
  }

  std::vector<std::string> *id_list;
  UserModelManager::UserModelManager *user_manager;
};

TEST_F(UserModelManagerTests, getUserWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_user = nlohmann::json::parse(user_manager->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_user["id"]) << "Wrong user received";
}

TEST_F(UserModelManagerTests, getUserWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_user = nlohmann::json::parse(user_manager->get(query.dump()));
  ASSERT_TRUE(received_user.find("error") != received_user.end())
                << "Doesn't return error on incorrect user id";
}

TEST_F(UserModelManagerTests, getUserWithoutId) {
  nlohmann::json query = {};
  nlohmann::json received_user = nlohmann::json::parse(user_manager->get(query.dump()));
  ASSERT_TRUE(received_user.find("error") != received_user.end()) << "Doesn't return error on incorrect data";
}

TEST_F(UserModelManagerTests, addCorrectUser) {
  nlohmann::json data = {
      {"email", "test1@bk.ru"},
      {"password", "123456"},
      {"nickname", "testuser1"}
  };
  nlohmann::json result = nlohmann::json::parse(user_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") == result.end()) << "The user has't been correctly added to the database";
}

TEST_F(UserModelManagerTests, addUserWithExistingEmail) {
  nlohmann::json data = {
      {"email", "test@bk.ru"},
      {"password", "123456"},
      {"nickname", "testuser2"}
  };
  nlohmann::json result = nlohmann::json::parse(user_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Added user with already existing email";
}

TEST_F(UserModelManagerTests, addUserWithExistingNickname) {
  nlohmann::json data = {
       {"email", "test2@bk.ru"},
      {"password", "123456"},
      {"nickname", "testuser"}
  };
  nlohmann::json result = nlohmann::json::parse(user_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Added user with already existing nickname";
}

TEST_F(UserModelManagerTests, checkExistingEmail) {
  nlohmann::json query = {
      {"email", "test@bk.ru"}
  };
  ASSERT_TRUE(user_manager->Contains(query.dump())) << "Doesn't find existing email";
}

TEST_F(UserModelManagerTests, checkNotExistingEmail) {
  nlohmann::json query = {
      {"email", "123"}
  };
  ASSERT_FALSE(user_manager->Contains(query.dump())) << "Find not existing email";
}

TEST_F(UserModelManagerTests, checkExistingNickname) {
  nlohmann::json query = {
      {"nickname", "testuser"}
  };
  ASSERT_TRUE(user_manager->Contains(query.dump())) << "Doesn't find existing nickname";
}

TEST_F(UserModelManagerTests, checkNotExistingNickname) {
  nlohmann::json query = {
      {"nickname", "123"}
  };
  ASSERT_FALSE(user_manager->Contains(query.dump())) << "Find not existing nickname";
}

