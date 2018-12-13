#ifndef THEQUESTS_HISTORYMODELMANAGER_H
#define THEQUESTS_HISTORYMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <core/model_manager/ModelManager.h>


namespace HistoryModelManager {
class HistoryModelManager : AbstractModelManager::AbstractModelManager {
 public:
  explicit HistoryModelManager() : AbstractModelManager::AbstractModelManager("History"){};
  std::string Create(const std::string &request);
  std::string Update(const std::string &request);
  std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string GetUserHistory(const std::string &request);
  ~HistoryModelManager() = default;
};
}

#endif //THEQUESTS_HISTORYMODELMANAGER_H
