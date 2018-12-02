//
// Created by Арсений Зорин on 30/11/2018.
//

#ifndef THEQUESTS_SESSIONMODELMANAGER_H
#define THEQUESTS_SESSIONMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <core/model_manager/ModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <openssl/sha.h>
#include <sstream>


namespace SessionModelManager {
  class SessionModelManager : AbstractModelManager::AbstractModelManager {
   public:
    explicit SessionModelManager() : AbstractModelManager::AbstractModelManager("Session") {};
    std::string get(const std::string &request, const std::vector<std::string> *projection = nullptr);
    std::string get_by_token(const std::string &request);
    std::string create(const std::string &request);
    std::string remove(const std::string &request);
    std::string update(const std::string &request);
    ~SessionModelManager() = default;
  };
}

#endif //THEQUESTS_SESSIONMODELMANAGER_H
