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
  std::string get(const std::string &request, const std::vector<std::string> *projection = nullptr);
  std::string create(const std::string &request);
  std::string remove(const std::string &request);
  std::string update(const std::string &request);
  ~CardLinkModelManager() = default;
};
}

#endif //THEQUESTS_CARDLINKMODELMANAGER_H
