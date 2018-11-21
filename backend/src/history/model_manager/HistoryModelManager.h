//
// Created by Арсений Зорин on 15/11/2018.
//
#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>
#include <quest/model_manager/QuestModelManager.h>

#ifndef THEQUESTS_HISTORYMODELMANAGER_H
#define THEQUESTS_HISTORYMODELMANAGER_H

namespace HistoryModelManager {
    class HistoryModelManager {
    public:
        explicit HistoryModelManager();

        std::string create(const std::string &request);

        std::string remove(const std::string &request);

        std::string update(const std::string &request);

        std::string get(const std::string &request);

    private:
        mongocxx::collection collection_;
        QuestModelManager::QuestModelManager *quest_manager_;
    };
}

#endif //THEQUESTS_HISTORYMODELMANAGER_H
