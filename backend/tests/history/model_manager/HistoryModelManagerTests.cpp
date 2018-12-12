//
// Created by Арсений Зорин on 15/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <quest/model_manager/QuestModelManager.h>
#include <history/model_manager/HistoryModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

// TODO: Добавить создания списка реальных юзеров
class HistoryModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["History"];
    auto quest_collection = (*client)["testdb"]["Quest"];
    quest_manager = new QuestModelManager::QuestModelManager();
    history_manager = new HistoryModelManager::HistoryModelManager();
    quest_id_list = new std::vector<std::string>;
    history_id_list = new std::vector<std::string>;
    user_id_list = new std::vector<std::string>;
    user_id_list->push_back(bsoncxx::oid().to_string());
    user_id_list->push_back(bsoncxx::oid().to_string());
    user_id_list->push_back(bsoncxx::oid().to_string());
    std::vector<nlohmann::json> quests;
    quests.push_back(nlohmann::json({
                                        {"title", "quest1"},
                                        {"description", "about quest1"},
                                        {"image", "image1"},
                                        {"resources", {"strength", "health", "wisdom"}},
                                    }));
    quests.push_back(nlohmann::json({
                                        {"title", "quest2"},
                                        {"description", "about quest2"},
                                        {"image", "image2"},
                                        {"resources", {"strength", "wisdom"}}
                                    }));
    for (const auto &quest : quests) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = quest_collection.insert_one((bsoncxx::from_json(quest.dump()).view()));
      quest_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
    nlohmann::json query;
    query["$set"]["firstCardId"]["$oid"] = bsoncxx::oid().to_string();
    query["$set"]["lossCardId"]["$oid"] = bsoncxx::oid().to_string();
    quest_collection.update_one(bsoncxx::builder::stream::document{}
                                    << "_id"
                                    << bsoncxx::oid((*quest_id_list)[0])
                                    << bsoncxx::builder::stream::finalize,
                                bsoncxx::from_json(query.dump()).view());
    quest_collection.update_one(bsoncxx::builder::stream::document{}
                                    << "_id"
                                    << bsoncxx::oid((*quest_id_list)[1])
                                    << bsoncxx::builder::stream::finalize,
                                bsoncxx::from_json(query.dump()).view());

    std::vector<nlohmann::json> histories;
    histories.push_back(nlohmann::json({
                                           {"questId", {{"$oid", (*quest_id_list)[0]}}},
                                           {"userId", {{"$oid", (*user_id_list)[0]}}},
                                           {"cardId", {{"$oid", bsoncxx::oid().to_string()}}},
                                           {"stage", "process"},
                                           {"resources", {
                                               {"health", 50},
                                               {"wisdom", 10}
                                           }}
                                       }));
    histories.push_back(nlohmann::json({
                                           {"questId", {{"$oid", (*quest_id_list)[1]}}},
                                           {"userId", {{"$oid", (*user_id_list)[0]}}},
                                           {"cardId", {{"$oid", bsoncxx::oid().to_string()}}},
                                           {"stage", "process"},
                                           {"resources", {
                                               {"health", 50},
                                               {"strength", 100}
                                           }}
                                       }));
    for (const auto &history : histories) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(history.dump()).view()));
      history_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete quest_id_list;
    delete history_id_list;
    delete user_id_list;
    delete history_manager;
    delete quest_manager;
  }

  std::vector<std::string> *quest_id_list;
  std::vector<std::string> *history_id_list;
  std::vector<std::string> *user_id_list;
  HistoryModelManager::HistoryModelManager *history_manager;
  QuestModelManager::QuestModelManager *quest_manager;

};

TEST_F(HistoryModelManagerTests, getHistoryWithExistingId) {
  nlohmann::json query = {
      {"questId", (*quest_id_list)[0]},
      {"userId", (*user_id_list)[0]},
      {"firstCardId", bsoncxx::oid().to_string()},
      {"resources", {"health", "strength"}}
  };
  nlohmann::json received_history = nlohmann::json::parse(history_manager->GetUserHistory(query.dump()));
  ASSERT_EQ((*history_id_list)[0], received_history["id"]) << "Wrong history received";
}

TEST_F(HistoryModelManagerTests, getHistoryWithIncorrectQuestId) {
  nlohmann::json query = {
      {"questId", ""},
      {"userId", (*user_id_list)[0]},
      {"resources", {"health", "strength"}}
  };
  nlohmann::json received_history = nlohmann::json::parse(history_manager->GetUserHistory(query.dump()));
  ASSERT_TRUE(received_history.find("error") != received_history.end())
                << "Doesn't return error on incorrect quest_manager id";
}

TEST_F(HistoryModelManagerTests, getHistoryWithIncorrectUserId) {
  nlohmann::json query = {
      {"questId", (*quest_id_list)[0]},
      {"userId", ""},
      {"resources", {"health", "strength"}}
  };
  nlohmann::json received_history = nlohmann::json::parse(history_manager->GetUserHistory(query.dump()));
  ASSERT_TRUE(received_history.find("error") != received_history.end()) << "Doesn't return error on incorrect user id";
}

TEST_F(HistoryModelManagerTests, getHistoryWithoutId) {
  nlohmann::json query = {};
  nlohmann::json received_quest = nlohmann::json::parse(history_manager->GetUserHistory(query.dump()));
  ASSERT_TRUE(received_quest.find("error") != received_quest.end()) << "Doesn't return error on incorrect data";
}

//TEST_F(HistoryModelManagerTests, getHistoryWithNotExictingQuestId) {
//  nlohmann::json query = {
//      {"questId", bsoncxx::oid().to_string()},
//      {"userId", (*user_id_list)[0]},
//      {"resources", {"health", "strength"}}
//  };
//  nlohmann::json received_history = nlohmann::json::parse(history_manager->GetUserHistory(query.dump()));
//  ASSERT_TRUE(received_history.find("error") != received_history.end())
//                << "Doesn't return error on not existing quest_manager id";
//}

TEST_F(HistoryModelManagerTests, createNotExistingHistory) {
  nlohmann::json query = {
      {"questId", (*quest_id_list)[0]},
      {"userId", (*user_id_list)[1]},
      {"firstCardId", bsoncxx::oid().to_string()},
      {"resources", {"health", "strength"}}
  };
  nlohmann::json received_new_history = nlohmann::json::parse(history_manager->Create(query.dump()));
  ASSERT_TRUE(received_new_history.find("error") == received_new_history.end())
                << "Return error on correct history data";
}

//TEST_F(HistoryModelManagerTests, createExistingHistory) {
//  nlohmann::json query = {
//      {"questId", (*quest_id_list)[0]},
//      {"userId", (*user_id_list)[0]},
//      {"firstCardId", bsoncxx::oid().to_string()},
//      {"resources", {"health", "strength"}}
//  };
//  nlohmann::json received_new_history = nlohmann::json::parse(history_manager->Create(query.dump()));
//  ASSERT_TRUE(received_new_history.find("error") != received_new_history.end())
//                << "Doesn't return error on already existing history";
//}

TEST_F(HistoryModelManagerTests, updateHistory) {
  nlohmann::json history_update_query = {
      {"id", (*history_id_list)[0]},
      {"cardId", bsoncxx::oid().to_string()},
      {"resources", {
          {"health", 25},
          {"strength", 100}
      }
      }
  };
  nlohmann::json new_history = nlohmann::json::parse(history_manager->Update(history_update_query.dump()));
  ASSERT_TRUE(
      history_update_query["cardId"] == new_history["cardId"] && history_update_query["resources"] == new_history["resources"])
                << "Incorrect history update";
}