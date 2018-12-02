//
// Created by Арсений Зорин on 15/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <quest/model_manager/QuestModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

class QuestModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["Quest"];
    quest_manager = new QuestModelManager::QuestModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> quests;
    quests.push_back(nlohmann::json({
                                        {"title", "quest1"},
                                        {"description", "about quest1"},
                                        {"image", "image1"},
                                        {"resources", {"strength", "health", "wisdom"}}
                                    }));
    quests.push_back(nlohmann::json({
                                        {"title", "quest2"},
                                        {"description", "about quest2"},
                                        {"image", "image2"},
                                        {"resources", {"strength", "wisdom"}}
                                    }));
    quests.push_back(nlohmann::json({
                                        {"title", "quest3"},
                                        {"description", "about quest3"},
                                        {"image", "image3"},
                                        {"resources", {"strength", "health", "wisdom", "respect"}}
                                    }));
    for (const auto &quest : quests) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(quest.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
  }

  std::vector<std::string> *id_list;
  QuestModelManager::QuestModelManager *quest_manager;
};

TEST_F(QuestModelManagerTests, addCorrectQuest) {
  nlohmann::json data = {
      {"title", "quest4"},
      {"description", "about quest4"},
      {"authorId", bsoncxx::oid().to_string()},
      {"image", "image4"},
      {"resources", {"health", "wisdom"}}
  };
  nlohmann::json inserted_quest = nlohmann::json::parse(quest_manager->create(data.dump()));
  ASSERT_TRUE(inserted_quest.find("error") == inserted_quest.end()) << "Get error on correct data";
  nlohmann::json query = {
      {"id", inserted_quest["id"]}
  };
  data["id"] = inserted_quest["id"];
  data["playerCount"] = 0;
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->get(query.dump()));
  ASSERT_TRUE(data == received_quest) << "The quest_manager has't been correctly added to the database";
}

TEST_F(QuestModelManagerTests, addIncorrectQuest) {
  nlohmann::json data = {
      {"description", "about quest4"},
      {"image", "image4"},
      {"resources", {"health", "wisdom"}}
  };
  nlohmann::json result = nlohmann::json::parse(quest_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Doesn't return error on incorrect data";
}

TEST_F(QuestModelManagerTests, getQuestWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_quest["id"]) << "Wrong quest_manager received";
}

TEST_F(QuestModelManagerTests, getQuestWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->get(query.dump()));
  ASSERT_TRUE(received_quest.find("error") != received_quest.end())
                << "Doesn't return error on incorrect quest_manager id";
}

TEST_F(QuestModelManagerTests, getQuestWithoutId) {
  nlohmann::json query = {};
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->get(query.dump()));
  ASSERT_TRUE(received_quest.find("error") != received_quest.end()) << "Doesn't return error on incorrect data";
}