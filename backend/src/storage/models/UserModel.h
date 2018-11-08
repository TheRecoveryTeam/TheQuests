//
// Created by Арсений Зорин on 03/11/2018.
//
#include <iostream>
#include <bsoncxx/json.hpp>
#include <string>


#ifndef USERMODEL_H
#define USERMODEL_H

namespace UserModel {
  class UserModel {
   public:
    explicit UserModel(const std::string &nickname, const std::string &email, const std::string &password);
    std::string create();
    std::string remove();
    std::string update();
    std::string get();
   private:
    std::string id_;
    std::string nickname_;
    std::string email_;
    std::string password_;

    bsoncxx::document::value ToDocument();
  };
}

#endif //USERMODEL_H
