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
    std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
    std::string GetByToken(const std::string &request);
    std::string Create(const std::string &request);
    std::string CreateByOauth2(const std::string &request);
    std::string Remove(const std::string &request);
    std::string Update(const std::string &request);
    ~SessionModelManager() = default;
  };
}

#endif //THEQUESTS_SESSIONMODELMANAGER_H
