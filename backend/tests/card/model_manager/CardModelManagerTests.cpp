//
// Created by Арсений Зорин on 11/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <card/model_manager/CardModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

class CardModelManagerTests : public ::testing::Test
{
 protected:
  void SetUp()
  {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["card"];
    card = new CardModelManager::CardModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> cards;
    cards.push_back(nlohmann::json({
         {"questId", "1"},
         {"title", "New card1"},
         {"description", "First project card"},
         {
             "links", {
             {"left way", "1"},
             {"right way", "2"}
         }
         },
         {"type", "choose"}
     }));
    cards.push_back(nlohmann::json({
         {"questId", "2"},
         {"title", "New card2"},
         {"description", "First project card"},
         {
             "links", {
             {"right way", "2"}
         }
         },
         {"type", "choose"}
     }));
    cards.push_back(nlohmann::json({
         {"questId", "1"},
         {"title", "New card3"},
         {"description", "Second project card"},
         {"type", "choose"}
     }));
    cards.push_back(nlohmann::json({
         {"questId", "2"},
         {"title", "New card4"},
         {"description", "Second project card"},
         {
             "links", {
             {"left way", "1"},
         }
         },
         {"type", "choose"}
     }));
    cards.push_back(nlohmann::json({
         {"questId", "1"},
         {"title", "New card5"},
         {"description", "Third project card"},
         {
             "links", {
             {"left way", "1"},
             {"right way", "2"}
         }
         },
         {"type", "choose"}
     }));
    for(const auto& card : cards) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one((bsoncxx::from_json(card.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown()
  {
    delete id_list;
  }

  std::vector<std::string>* id_list;
  CardModelManager::CardModelManager* card;
};

TEST_F(CardModelManagerTests, addCorrectCard) {
  nlohmann::json data = {
      {"questId", "1"},
      {"title", "New card"},
      {"description", "First project card"},
      {
          "links", {
          {"left way", "1"},
          {"right way", "2"}
          }
      },
      {"type", "choose"}
  };
  nlohmann::json inserted_card = nlohmann::json::parse(card->create(data.dump()));
  nlohmann::json query = {
      {"_id", inserted_card["_id"]}
  };
  nlohmann::json received_card = nlohmann::json::parse(card->get(data.dump()));
  ASSERT_EQ(inserted_card["_id"], received_card["_id"]["$oid"]) << "The card has't been added to the database";
}


TEST_F(CardModelManagerTests, addIncorrectCard) {
  nlohmann::json data = {
      {"questId", "1"},
      {"description", "First project card"},
      {
          "links", {
          {"left way", "1"},
          {"right way", "2"}
      }
      },
      {"type", "choose"}
  };
  nlohmann::json result = nlohmann::json::parse(card->create(data.dump()));
  ASSERT_TRUE(result.find("error") != result.end()) << "Doesn't return error on incorrect data";
}


TEST_F(CardModelManagerTests, getCardWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_card = nlohmann::json::parse(card->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_card["_id"]["$oid"]) << "Wrong card received";
}


TEST_F(CardModelManagerTests, getCardWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_card = nlohmann::json::parse(card->get(query.dump()));
  ASSERT_TRUE(received_card.find("error") != received_card.end()) << "Doesn't return error on incorrect card id";
}


TEST_F(CardModelManagerTests, getCardWithoutId) {
  nlohmann::json query = {
      {"questId", "1"}
  };
  nlohmann::json received_card = nlohmann::json::parse(card->get(query.dump()));
  ASSERT_TRUE(received_card.find("error") != received_card.end()) << "Doesn't return error on incorrect data";
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
  auto uri = mongocxx::uri{"mongodb://localhost:27018"};
  MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                                 bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));
  return RUN_ALL_TESTS();
}

