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
    std::string Create(const std::string &request);
    std::string CreateByOauth2(const std::string &request);
    std::string Remove(const std::string &request);
    std::string Update(const std::string &request);
    std::string Login(const std::string &request);
    std::string LoginByOauth2(const std::string &request);
    std::string Logout(const std::string &request);
    bool Contains(const std::string &request);
    ~UserModelManager();

   private:
    SessionModelManager::SessionModelManager* session_manager_;
  };
}

#endif //THEQUESTS_USERMODELMANAGER_H
