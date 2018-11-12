//
// Created by Арсений Зорин on 11/11/2018.
//
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <models/CardModel.h>
#include <connections/Connection_singleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <sstream>

class CardModelTest : public ::testing::Test {
protected:
    void SetUp() {

    }

    void TearDown() {
    }
};

TEST_F(CardModelTest, addCorrectCard
) {
nlohmann::json data = {
        {"questId",     "1"},
        {"title",       "New card"},
        {"description", "First project card"},
        {
         "links",       {
                                {"left way", "1"},
                                {"right way", "2"}
                        }
        },
        {"type",        "choose"}
};
CardModel::CardModel card = CardModel::CardModel(data.dump());
nlohmann::json inserted_card = nlohmann::json::parse(card.create());
nlohmann::json query = {
        {"_id", inserted_card["_id"]}
};
nlohmann::json received_card = nlohmann::json::parse(CardModel::CardModel(query.dump()).get());
ASSERT_EQ(inserted_card["_id"], received_card["_id"]["$oid"]
) << "The card has't been added to the database";
}


TEST_F(CardModelTest, addIncorrectCard
) {
nlohmann::json data = {
        {"questId",     "1"},
        {"description", "First project card"},
        {
         "links",       {
                                {"left way", "1"},
                                {"right way", "2"}
                        }
        },
        {"type",        "choose"}
};
CardModel::CardModel card = CardModel::CardModel(data.dump());
nlohmann::json result = nlohmann::json::parse(card.create());
ASSERT_TRUE(result
.find("error") != result.

end()

) << "Doesn't return error on incorrect data";
}


TEST_F(CardModelTest, getCardWithExistingId
) {
auto client = MongoAccess::MongoAccess::instance().get_connection();
auto collection = (*client)["testdb"]["card"];
auto card_value = bsoncxx::builder::stream::document{}
        << "questId" << "1"
        << "description" << "First project card"
        << "type" << "choose"
        << bsoncxx::builder::stream::finalize;
auto inserted_card = collection.insert_one(card_value.view());
std::string inserted_card_id = (*inserted_card).inserted_id().get_oid().value.to_string();
nlohmann::json query = {
        {"_id", inserted_card_id}
};
nlohmann::json received_card = nlohmann::json::parse(CardModel::CardModel(query.dump()).get());
ASSERT_EQ(inserted_card_id, received_card["_id"]["$oid"]
) << "Wrong card received";
}


TEST_F(CardModelTest, getCardWithIncorrectId
) {
nlohmann::json query = {
        {"_id", ""}
};
nlohmann::json received_card = nlohmann::json::parse(CardModel::CardModel(query.dump()).get());
ASSERT_TRUE(received_card
.find("error") != received_card.

end()

) << "Doesn't return error on incorrect card id";
}


TEST_F(CardModelTest, getCardWithoutId
) {
nlohmann::json query = {
        {"questId", "1"}
};
nlohmann::json received_card = nlohmann::json::parse(CardModel::CardModel(query.dump()).get());
ASSERT_TRUE(received_card
.find("error") != received_card.

end()

) << "Doesn't return error on incorrect data";
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
    auto uri = mongocxx::uri{"mongodb://localhost:27018"};
    MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                                   bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));
    return RUN_ALL_TESTS();
}

