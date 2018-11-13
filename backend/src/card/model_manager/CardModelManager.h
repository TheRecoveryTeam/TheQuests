//
// Created by Арсений Зорин on 10/11/2018.
//
#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>

#ifndef THEQUESTS_CARDMODELMANAGER_H
#define THEQUESTS_CARDMODELMANAGER_H

namespace CardModelManager {
  class CardModelManager {
   public:
    explicit CardModelManager();
    std::string create(const std::string& request);
    std::string remove(const std::string& request);
    std::string update(const std::string& request);
    std::string get(const std::string& request);
    std::string get_by_quest(const std::string& request);

   private:
    mongocxx::collection collection_;
  };
}

#endif //THEQUESTS_CARDMODELMANAGER_H
