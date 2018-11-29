//
// Created by Арсений Зорин on 15/11/2018.
//
#ifndef THEQUESTS_QUESTMODELMANAGER_H
#define THEQUESTS_QUESTMODELMANAGER_H

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

namespace QuestModelManager {
class QuestModelManager : public AbstractModelManager::AbstractModelManager {
 public:
  explicit QuestModelManager() : AbstractModelManager::AbstractModelManager("Quest") {};
  std::string get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string create(const std::string &request);
  std::string remove(const std::string &request);
  std::string update(const std::string &request);
};
}

#endif //THEQUESTS_QUESTMODELMANAGER_H
