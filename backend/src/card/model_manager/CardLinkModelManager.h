//
// Created by Арсений Зорин on 15/11/2018.
//
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
  std::string Create(const std::string &request);
  std::string Remove(const std::string &request);
  std::string Update(const std::string &request);
  ~CardLinkModelManager() = default;
};
}

#endif //THEQUESTS_CARDLINKMODELMANAGER_H
