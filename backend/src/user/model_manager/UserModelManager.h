//
// Created by Арсений Зорин on 30/11/2018.
//

#ifndef THEQUESTS_USERMODELMANAGER_H
#define THEQUESTS_USERMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <core/model_manager/ModelManager.h>
#include <session/model_manager/SessionModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <openssl/sha.h>
#include <sstream>


namespace UserModelManager {
  class UserModelManager : public AbstractModelManager::AbstractModelManager {
   public:
    explicit UserModelManager();
    std::string create(const std::string &request);
    std::string remove(const std::string &request);
    std::string update(const std::string &request);
    std::string login(const std::string &request);
    std::string logout(const std::string &request);
    bool Contains(const std::string &request);
    ~UserModelManager();

   private:
    SessionModelManager::SessionModelManager* session_manager_;
  };
}

#endif //THEQUESTS_USERMODELMANAGER_H
