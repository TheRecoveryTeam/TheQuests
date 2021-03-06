#ifndef THEQUESTS_CARDMODELMANAGER_H
#define THEQUESTS_CARDMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <quest/model_manager/QuestModelManager.h>
#include <history/model_manager/HistoryModelManager.h>
#include <card/model_manager/CardLinkModelManager.h>
#include <core/model_manager/ModelManager.h>


namespace CardModelManager {
class CardModelManager : AbstractModelManager::AbstractModelManager{
 public:
  explicit CardModelManager();
  std::string Create(const std::string &request);
  std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string GetNextCard(const std::string &request);
  ~CardModelManager();

 private:
  QuestModelManager::QuestModelManager *quest_manager_;
  CardLinkModelManager::CardLinkModelManager *cardlink_manager_;
  HistoryModelManager::HistoryModelManager *history_manager_;
};
}

#endif //THEQUESTS_CARDMODELMANAGER_H
