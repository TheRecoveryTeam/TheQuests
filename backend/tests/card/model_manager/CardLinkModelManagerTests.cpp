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
    card_id_list = new std::vector<std::string>;
    for (int i = 0; i < 4; ++i) {
      card_id_list->push_back(bsoncxx::oid().to_string());
    }
    std::vector<nlohmann::json> card_links;
    card_links.push_back(nlohmann::json({
                                            {"toId", {{"$oid", (*card_id_list)[0]}}},
                                            {"weight", {
                                                {"strength", -100},
                                                {"health", 200}
                                            }}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"toId", {{"$oid", (*card_id_list)[1]}}},
                                            {"weight", {
                                                {"strength", 10},
                                                {"health", 20}
                                            }}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"toId", {{"$oid", (*card_id_list)[2]}}},
                                            {"weight", {
                                                {"strength", 0},
                                                {"health", 1}
                                            }}
                                        }));
    card_links.push_back(nlohmann::json({
                                            {"toId", {{"$oid", (*card_id_list)[3]}}},
                                            {"weight", {
                                                {"strength", 10},
                                                {"health", -5}
                                            }}
                                        }));
    for (const auto &card_link : card_links) {
      bsoncxx::stdx::optional<mongocxx::result::insert_one>
          result = collection.insert_one((bsoncxx::from_json(card_link.dump()).view()));
      id_list->push_back((*result).inserted_id().get_oid().value.to_string());
    }
  }
  void TearDown() {
    delete id_list;
    delete card_id_list;
  }

  std::vector<std::string> *id_list;
  std::vector<std::string> *card_id_list;
  CardLinkModelManager::CardLinkModelManager *card_link_manager;
};

TEST_F(CardLinkModelManagerTests, getCardLinkWithExistingId) {
  nlohmann::json query = {
      {"id", (*id_list)[0]}
  };
  nlohmann::json received_card_link = nlohmann::json::parse(card_link_manager->get(query.dump()));
  ASSERT_EQ((*id_list)[0], received_card_link["id"]) << "Wrong card link received";
  ASSERT_EQ((*card_id_list)[0], received_card_link["toId"]) << "Wrong toId received";
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