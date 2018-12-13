#ifndef THEQUESTS_CARDLINKMODELMANAGER_H
#define THEQUESTS_CARDLINKMODELMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <core/model_manager/ModelManager.h>


namespace CardLinkModelManager {
class CardLinkModelManager : AbstractModelManager::AbstractModelManager{
 public:
  explicit CardLinkModelManager() : AbstractModelManager("CardLink") {};
  std::string Get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  ~CardLinkModelManager() = default;
};
}

#endif //THEQUESTS_CARDLINKMODELMANAGER_H
