//
// Created by Арсений Зорин on 10/11/2018.
//
#include <iostream>
#include <bsoncxx/json.hpp>
#include <string>
#include <map>

#ifndef CARDMODEL_H
#define CARDMODEL_H

namespace CardModel {
    class CardModel {

    public:
        explicit CardModel(const std::string &json);

        std::string create();

        std::string remove();

        std::string update();

        std::string get();

        std::string get_by_quest();

    private:
        std::string id_;
        std::string quest_id_;
        std::string title_;
        std::string image_path_;
        std::string description_;
        std::map<std::string, std::string> links_;
        std::string type_;
    };
}

#endif //CARDMODEL_H
