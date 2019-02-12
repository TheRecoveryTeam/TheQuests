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
    user_manager = new UserModelManager::UserModelManager();
    nlohmann::json new_user = {
        {"email", "testquest@mail.ru"},
        {"nickname", "forQuests"}
    };
    if (!user_manager->Contains(new_user.dump())) {
      new_user["password"] = "123";
      author_id = nlohmann::json::parse(user_manager->Create(new_user.dump()))["id"];
    } else {
      new_user["password"] = "123";
      author_id = nlohmann::json::parse(user_manager->Login(new_user.dump()))["id"];
    }
    quest_manager = new QuestModelManager::QuestModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> quests;
    quests.push_back(nlohmann::json({
      {"title", "quest1"},
      {"description", "about quest1"},
      {"image", "image1"},
      {"resources", {"strength", "health", "wisdom"}},
      {"authorId", {{"$oid", author_id}}}
    }));
    quests.push_back(nlohmann::json({
      {"title", "quest2"},
      {"description", "about quest2"},
      {"image", "image2"},
      {"resources", {"strength", "wisdom"}},
      {"authorId", {{"$oid", author_id}}}
    }));
    quests.push_back(nlohmann::json({
      {"title", "quest3"},
      {"description", "about quest3"},
      {"image", "image3"},
      {"resources", {"strength", "health", "wisdom", "respect"}},
      {"authorId", {{"$oid", author_id}}}
    }));
    for (const auto &quest : quests) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(quest.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
    delete quest_manager;
//    delete user_manager;
  }

  std::string author_id;
  std::vector<std::string> *id_list;
  QuestModelManager::QuestModelManager *quest_manager;
  UserModelManager::UserModelManager *user_manager;
};

TEST_F(QuestModelManagerTests, addCorrectQuest) {
  nlohmann::json data = {
    {"title", "quest4"},
    {"description", "about quest4"},
    {"authorId", bsoncxx::oid().to_string()},
    {"image", "image4"},
    {"resources", {"health", "wisdom"}}
  };
  nlohmann::json inserted_quest = nlohmann::json::parse(quest_manager->Create(data.dump()));
  ASSERT_TRUE(inserted_quest.find("error") == inserted_quest.end()) << "Get error on correct data";
  nlohmann::json query = {
      {"id", inserted_quest["id"]}
  };
  data["id"] = inserted_quest["id"];
  data["playerCount"] = 0;
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->Get(query.dump()));
  ASSERT_TRUE(data == received_quest) << "The quest_manager has't been correctly added to the database";
}

TEST_F(QuestModelManagerTests, addIncorrectQuest) {
  nlohmann::json data = {
    {"description", "about quest4"},
    {"image", "image4"},
    {"resources", {"health", "wisdom"}}
  };
  nlohmann::json result = nlohmann::json::parse(quest_manager->Create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Doesn't return error on incorrect data";
}

TEST_F(QuestModelManagerTests, getQuestWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->Get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_quest["id"]) << "Wrong quest_manager received";
}

TEST_F(QuestModelManagerTests, getQuestWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->Get(query.dump()));
  ASSERT_TRUE(received_quest.find("error") != received_quest.end())
                << "Doesn't return error on incorrect quest_manager id";
}

TEST_F(QuestModelManagerTests, getQuestWithoutId) {
  nlohmann::json query = {};
  nlohmann::json received_quest = nlohmann::json::parse(quest_manager->Get(query.dump()));
  ASSERT_TRUE(received_quest.find("error") != received_quest.end()) << "Doesn't return error on incorrect data";
}

TEST_F(QuestModelManagerTests, getQuestList) {
  nlohmann::json query = {
      {"page", 2},
      {"limit", 2}
  };
  auto result = nlohmann::json::parse(quest_manager->List(query.dump()));
  ASSERT_TRUE(result.find("error") == result.end()) << "Return error on correct query";
}

TEST_F(QuestModelManagerTests, getAuthorQuestList) {
  nlohmann::json query = {
      {"page", 2},
      {"limit", 2},
      {"authorId", author_id}
  };
  auto result = nlohmann::json::parse(quest_manager->List(query.dump()));
  ASSERT_TRUE(result.find("error") == result.end()) << "Return error on correct query";
}

TEST_F(QuestModelManagerTests, getUserQuestList) {
  nlohmann::json query = {
      {"page", 2},
      {"limit", 2},
      {"authorId", author_id}
  };
  auto result = nlohmann::json::parse(quest_manager->List(query.dump()));
  std::cout << result << std::endl;
  ASSERT_TRUE(result.find("error") == result.end()) << "Return error on correct query";
}