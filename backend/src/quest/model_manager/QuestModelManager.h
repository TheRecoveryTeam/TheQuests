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
#include <history/model_manager/HistoryModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

namespace QuestModelManager {
class QuestModelManager : public AbstractModelManager::AbstractModelManager {
 public:
  explicit QuestModelManager();
  std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string GetWithHistory(const std::string &request);
  std::string Create(const std::string &request);
  std::string Remove(const std::string &request);
  std::string Update(const std::string &request);
  ~QuestModelManager();
 private:
  HistoryModelManager::HistoryModelManager *history_manager_;
};
}

#endif //THEQUESTS_QUESTMODELMANAGER_H
