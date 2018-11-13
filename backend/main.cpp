#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>


int main(int, char**) {
  auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
  auto uri = mongocxx::uri{"mongodb://localhost:27018"};
  MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                     bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));
  return 0;
}