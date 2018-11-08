//
// Created by Арсений Зорин on 03/11/2018.
//
#include <bsoncxx/builder/stream/document.hpp>
#include "UserModel.h"
#include <mongocxx/client.hpp>


UserModel::UserModel::UserModel(const std::string &nickname, const std::string &email, const std::string &password): nickname_(nickname), email_(email), password_(password) {};

std::string UserModel::UserModel::create() {
  if (nickname_.empty() || email_.empty() || password_.empty()) {
    bsoncxx::document::value error = bsoncxx::builder::stream::document{}
        << "error" << "NotEnoughData"
        << bsoncxx::builder::stream::finalize;
    return bsoncxx::to_json(error.view());
  }
  bsoncxx::document::value user_value = ToDocument();
  mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27018"}};
  auto collection = conn["testdb"]["user"];
  collection.insert_one(user_value.view());
  return bsoncxx::to_json(user_value.view());
}

bsoncxx::document::value UserModel::UserModel::ToDocument() {
  auto builder = bsoncxx::builder::stream::document{};
  if (!nickname_.empty()) {
    builder << "nickname" << this->nickname_;
  }
  if (!email_.empty()) {
    builder << "email" << this->email_;
  }
  if (!password_.empty()) {
    builder << "password" << this->password_;
  }
  bsoncxx::document::value user_value = builder << bsoncxx::builder::stream::finalize;
  return user_value;
}

std::string UserModel::UserModel::get() {
  mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27018"}};
  auto collection = conn["testdb"]["user"];
  bsoncxx::stdx::optional<bsoncxx::document::value> result = collection.find_one(ToDocument());
  if (result) {
    return bsoncxx::to_json(*result);
  }
  bsoncxx::document::value error = bsoncxx::builder::stream::document{}
    << "error" << "UserDoesNotExist"
    << bsoncxx::builder::stream::finalize;
  return bsoncxx::to_json(error.view());
}


