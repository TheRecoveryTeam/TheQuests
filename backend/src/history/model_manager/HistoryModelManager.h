//
// Created by Арсений Зорин on 15/11/2018.
//
#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <quest/model_manager/QuestModelManager.h>
#include <core/model_manager/ModelManager.h>

#ifndef THEQUESTS_HISTORYMODELMANAGER_H
#define THEQUESTS_HISTORYMODELMANAGER_H

namespace HistoryModelManager {
class HistoryModelManager : AbstractModelManager::AbstractModelManager{
 public:
  explicit HistoryModelManager();
  std::string create(const std::string &request);
  std::string remove(const std::string &request);
  std::string update(const std::string &request);
  std::string get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string get_user_history(const std::string &request);
  ~HistoryModelManager();

 private:
  QuestModelManager::QuestModelManager *quest_manager_;
};
}

#endif //THEQUESTS_HISTORYMODELMANAGER_H
