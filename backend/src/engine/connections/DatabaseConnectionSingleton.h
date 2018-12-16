#ifndef THEQUESTS_DATABASE_CONNECTION_SINGLETON_H
#define THEQUESTS_DATABASE_CONNECTION_SINGLETON_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>


namespace MongoAccess {
class MongoAccess {
 public:
  static MongoAccess &instance();
  void configure(std::unique_ptr<mongocxx::instance> instance,
                 std::unique_ptr<mongocxx::pool> pool);
  using connection = mongocxx::pool::entry;
  connection get_connection();
  bsoncxx::stdx::optional<connection> try_get_connection();

 private:
  MongoAccess() = default;
  std::unique_ptr<mongocxx::instance> _instance = nullptr;
  std::unique_ptr<mongocxx::pool> _pool = nullptr;
};
}

#endif //THEQUESTS_DATABASE_CONNECTION_SINGLETON_H
