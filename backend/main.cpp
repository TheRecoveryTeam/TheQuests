#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
//#include "src/storage/models/UserModel.h"
//#include <models/UserModel.h>
#include <card/model_manager/CardModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>


int main(int, char**) {
  auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
  auto uri = mongocxx::uri{"mongodb://localhost:27018"};
  MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                     bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));
  auto card_value = bsoncxx::builder::stream::document{}
    << "quest_id" << "1"
    << "title" << "New card"
    << "description" << "First project card"
    << "links" << bsoncxx::builder::stream::open_document
    << "left way" << "1"
    << "right way" << "2"
    << bsoncxx::builder::stream::close_document
    << "type" << "choose"
    << bsoncxx::builder::stream::finalize;
    CardModel::CardModel card = CardModel::CardModel(bsoncxx::to_json(card_value.view()));
    std::cout << card.create() << std::endl;
    auto card_value_find = bsoncxx::builder::stream::document{}
    << "_id" << "5be844d97af918d6be567092"
    << bsoncxx::builder::stream::finalize;
    CardModel::CardModel card_find = CardModel::CardModel(bsoncxx::to_json(card_value_find.view()));
    std::cout << card_find.get();
  return 0;
}