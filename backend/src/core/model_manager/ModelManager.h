#ifndef THEQUESTS_MODELMANAGER_H
#define THEQUESTS_MODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <utils/model_manager/DataManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

namespace AbstractModelManager {
class AbstractModelManager {
 public:
    explicit AbstractModelManager(const std::string &collection_name);
    std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
    ~AbstractModelManager() = default;

 protected:
    mongocxx::collection collection_;
    std::string collection_name_;
  };
}

#endif //THEQUESTS_MODELMANAGER_H
