#ifndef THEQUESTS_QUESTMODELMANAGER_H
#define THEQUESTS_QUESTMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <core/model_manager/ModelManager.h>
#include <history/model_manager/HistoryModelManager.h>
#include <user/model_manager/UserModelManager.h>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>


namespace QuestModelManager {
class QuestModelManager : public AbstractModelManager::AbstractModelManager {
 public:
  explicit QuestModelManager();
  std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string GetWithHistory(const std::string &request);
  std::string Create(const std::string &request);
  std::string List(const std::string &request);
  ~QuestModelManager();
 private:
  HistoryModelManager::HistoryModelManager *history_manager_;
  UserModelManager::UserModelManager *user_manager_;
};
}

#endif //THEQUESTS_QUESTMODELMANAGER_H
