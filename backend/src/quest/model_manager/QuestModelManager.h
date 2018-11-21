//
// Created by Арсений Зорин on 15/11/2018.
//
#include <iostream>
#include <string>
#include <map>
#include <mongocxx/client.hpp>

#ifndef THEQUESTS_QUESTMODELMANAGER_H
#define THEQUESTS_QUESTMODELMANAGER_H

namespace QuestModelManager {
    class QuestModelManager {
    public:
        explicit QuestModelManager();

        std::string create(const std::string &request);

        std::string remove(const std::string &request);

        std::string update(const std::string &request);

        std::string get(const std::string &request);

    private:
        mongocxx::collection collection_;
    };
}

#endif //THEQUESTS_QUESTMODELMANAGER_H
