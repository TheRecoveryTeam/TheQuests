//
// Created by Арсений Зорин on 15/11/2018.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <card/model_manager/CardLinkModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <vector>

class CardLinkModelManagerTests : public ::testing::Test {
 protected:
  void SetUp() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    auto collection = (*client)["testdb"]["CardLink"];
    card_link_manager = new CardLinkModelManager::CardLinkModelManager();
    id_list = new std::vector<std::string>;
    std::vector<nlohmann::json> card_links;
    card_links.push_back(nlohmann::json({
                                            {"name", "strength"}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"name", "health"}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"name", "wisdom"}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"name", "respect"}
                                        }));
    for (const auto &card_link : card_links) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(card_link.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
  }

  std::vector<std::string> *id_list;
  CardLinkModelManager::CardLinkModelManager *card_link_manager;
};

TEST_F(CardLinkModelManagerTests, getCardLinkWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_card_link = nlohmann::json::parse(card_link_manager->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_card_link["_id"]["$oid"]) << "Wrong card link received";
}

TEST_F(CardLinkModelManagerTests, getCardLinkWithIncorrectId) {
  nlohmann::json query = {
      {"id", ""}
  };
  nlohmann::json received_card_link = nlohmann::json::parse(card_link_manager->get(query.dump()));
  ASSERT_TRUE(received_card_link.find("error") != received_card_link.end())
                << "Doesn't return error on incorrect card link id";
}

TEST_F(CardLinkModelManagerTests, getCardLinkWithoutId) {
  nlohmann::json query = {};
  nlohmann::json received_card_link = nlohmann::json::parse(card_link_manager->get(query.dump()));
  ASSERT_TRUE(received_card_link.find("error") != received_card_link.end()) << "Doesn't return error on incorrect data";
}