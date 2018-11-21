//
// Created by Арсений Зорин on 11/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <card/model_manager/CardModelManager.h>
#include <quest/model_manager/QuestModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

class CardModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["Card"];
    auto quest_collection = (*client)["testdb"]["Quest"];
    auto card_link_collection = (*client)["testdb"]["CardLink"];
    quest_manager = new QuestModelManager::QuestModelManager();
    card_manager = new CardModelManager::CardModelManager();
    quest_id_list = new std::vector<std::string>;
    card_id_list = new std::vector<std::string>;
    card_link_id_list = new std::vector<std::string>;
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
    for (const auto &quest : quests) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = quest_collection.insert_one((bsoncxx::from_json(quest.dump()).view()));
      quest_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
    std::vector<nlohmann::json> cards;
    std::vector<nlohmann::json> card_links;
    cards.push_back(nlohmann::json({
                                       {"questId", (*quest_id_list)[0]},
                                       {"title", "EndCard"},
                                       {"description", "End quest card"},
                                       {"type", "finish"}
                                   }));
    bsoncxx::stdx::optional<mongocxx::result::insert_one>
        result = collection.insert_one((bsoncxx::from_json(cards[0].dump()).view()));
    card_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    card_links.push_back(nlohmann::json({
                                            {"toId", (*card_id_list)[0]},
                                            {"weight", {
                                                {"strength", -10},
                                                {"health", -15}
                                            }}
                                        }));
    result = card_link_collection.insert_one((bsoncxx::from_json(card_links[0].dump()).view()));
    card_link_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    card_links.push_back(nlohmann::json({
                                            {"toId", ""},
                                            {"weight", {
                                                {"strength", -100},
                                                {"health", 200}
                                            }}
                                        }));
    result = card_link_collection.insert_one((bsoncxx::from_json(card_links[1].dump()).view()));
    card_link_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    cards.push_back(nlohmann::json({
                                       {"questId", (*quest_id_list)[0]},
                                       {"title", "RightCard"},
                                       {"description", "Right quest card"},
                                       {
                                           "links", {
                                           {"lose", (*card_link_id_list)[1]}
                                       }
                                       },
                                       {"type", "choose"}
                                   }));
    result = collection.insert_one((bsoncxx::from_json(cards[1].dump()).view()));
    card_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    card_links.push_back(nlohmann::json({
                                            {"toId", (*card_id_list)[1]},
                                            {"weight", {
                                                {"strength", 10},
                                                {"health", 15}
                                            }}
                                        }));
    result = card_link_collection.insert_one((bsoncxx::from_json(card_links[2].dump()).view()));
    card_link_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    cards.push_back(nlohmann::json({
                                       {"questId", (*quest_id_list)[0]},
                                       {"title", "FirstCard"},
                                       {"description", "First quest card"},
                                       {
                                           "links", {
                                           {"left card", (*card_link_id_list)[0]},
                                           {"right card", (*card_link_id_list)[2]}
                                       }
                                       },
                                       {"type", "choose"}
                                   }));
    result = collection.insert_one((bsoncxx::from_json(cards[2].dump()).view()));
    card_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    cards.push_back(nlohmann::json({
                                       {"questId", (*quest_id_list)[0]},
                                       {"title", "GAMEOVER"},
                                       {"description", "YOU LOSE"},
                                       {"type", "choose"}
                                   }));
    result = collection.insert_one((bsoncxx::from_json(cards[3].dump()).view()));
    card_id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    nlohmann::json query;
    query["$set"]["firstCardId"] = (*card_id_list)[2];
    query["$set"]["lossCardId"] = (*card_id_list)[3];
    quest_collection.update_one(bsoncxx::builder::stream::document{}
                                    << "_id"
                                    << bsoncxx::oid((*quest_id_list)[0])
                                    << bsoncxx::builder::stream::finalize,
                                bsoncxx::from_json(query.dump()).view());
  }
  void TearDown() {
    delete card_id_list;
  }

  std::vector<std::string> *card_id_list;
  std::vector<std::string> *quest_id_list;
  std::vector<std::string> *card_link_id_list;
  CardModelManager::CardModelManager *card_manager;
  QuestModelManager::QuestModelManager *quest_manager;
};

TEST_F(CardModelManagerTests, addCorrectCard) {
  nlohmann::json data = {
      {"questId", (*quest_id_list)[0]},
      {"title", "New card_manager"},
      {"description", "First project card_manager"},
      {
          "links", {
          {"left way", "1"},
          {"right way", "2"}
      }
      },
      {"type", "choose"}
  };
  nlohmann::json inserted_card = nlohmann::json::parse(card_manager->create(data.dump()));
  ASSERT_TRUE(inserted_card.find("error") == inserted_card.end()) << "Get error on correct data";
  nlohmann::json query = {
      {"cardId", inserted_card["_id"]}
  };
  nlohmann::json received_card = nlohmann::json::parse(card_manager->get(query.dump()));
  ASSERT_EQ(inserted_card["_id"], received_card["_id"]["$oid"]) << "The card_manager has't been added to the database";
}

TEST_F(CardModelManagerTests, addIncorrectCard) {
  nlohmann::json data = {
      {"questId", "1"},
      {"description", "First project card_manager"},
      {
          "links", {
          {"left way", "1"},
          {"right way", "2"}
      }
      },
      {"type", "choose"}
  };
  nlohmann::json result = nlohmann::json::parse(card_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Doesn't return error on incorrect data";
}

TEST_F(CardModelManagerTests, addCardWithNotExistingQuestId) {
  nlohmann::json data = {
      {"questId", bsoncxx::oid().to_string()},
      {"description", "First project card_manager"},
      {
          "links", {
          {"left way", "1"},
          {"right way", "2"}
      }
      },
      {"type", "choose"}
  };
  nlohmann::json result = nlohmann::json::parse(card_manager->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Doesn't return error on not existing quest id";
}

TEST_F(CardModelManagerTests, getCardWithExistingId) {
  nlohmann::json query = {
      {"cardId", (*card_id_list)[0]}
  };
  nlohmann::json received_card = nlohmann::json::parse(card_manager->get(query.dump()));
  ASSERT_EQ((*card_id_list)[0], received_card["_id"]["$oid"]) << "Wrong card received";
}

TEST_F(CardModelManagerTests, getCardWithIncorrectId) {
  nlohmann::json query = {
      {"cardId", ""}
  };
  nlohmann::json received_card = nlohmann::json::parse(card_manager->get(query.dump()));
  ASSERT_TRUE(received_card.find("error") != received_card.end()) << "Doesn't return error on incorrect caed id";
}

TEST_F(CardModelManagerTests, getCardWithoutId) {
  nlohmann::json query = {
      {"questId", "1"}
  };
  nlohmann::json received_card = nlohmann::json::parse(card_manager->get(query.dump()));
  ASSERT_TRUE(received_card.find("error") != received_card.end()) << "Doesn't return error on incorrect data";
}

TEST_F(CardModelManagerTests, getNextEndCard) {
  nlohmann::json query = {
      {"userId", bsoncxx::oid().to_string()},
      {"cardId", (*card_id_list)[2]},
      {"answer", "left card"}
  };
  nlohmann::json result = nlohmann::json::parse(card_manager->get_next_card(query.dump()));
  nlohmann::json expected_result = {
      {"nextCardId", (*card_id_list)[0]},
      {"resources", {
          {"strength", 40},
          {"health", 35},
          {"wisdom", 50}
      }}
  };
  ASSERT_TRUE(expected_result == result) << "Incorrect get end next card";
}

TEST_F(CardModelManagerTests, getNextCard) {
  nlohmann::json query = {
      {"userId", bsoncxx::oid().to_string()},
      {"cardId", (*card_id_list)[2]},
      {"answer", "right card"}
  };
  nlohmann::json result = nlohmann::json::parse(card_manager->get_next_card(query.dump()));
  nlohmann::json expected_result = {
      {"nextCardId", (*card_id_list)[1]},
      {"resources", {
          {"strength", 60},
          {"health", 65},
          {"wisdom", 50}
      }}
  };
  ASSERT_TRUE(expected_result == result) << "Incorrect get next card";
}

TEST_F(CardModelManagerTests, getNextLoseCard) {
  nlohmann::json query = {
      {"userId", bsoncxx::oid().to_string()},
      {"cardId", (*card_id_list)[1]},
      {"answer", "lose"}
  };
  nlohmann::json result = nlohmann::json::parse(card_manager->get_next_card(query.dump()));
  nlohmann::json expected_result = {
      {"nextCardId", (*card_id_list)[3]},
      {"resources", {
          {"strength", 0},
          {"health", 100},
          {"wisdom", 50}
      }}
  };
  ASSERT_TRUE(expected_result == result) << "Incorrect get lose next card";
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
  auto uri = mongocxx::uri{"mongodb://localhost:27018"};
  MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                                 bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));
  return RUN_ALL_TESTS();
}

