//
// Created by Арсений Зорин on 27/11/2018.
//
#include <utils/model_manager/DataManager.h>


bool DataManager::CheckRequiredParameters(const nlohmann::json &data, std::vector<std::string> keys) {
  for (auto& key : keys) {
    if (data.find(key) == data.end()) {
      return false;
    }
  }
  return true;
}

bool DataManager::CheckIdCorrectness(const nlohmann::json &data, std::vector<std::string> keys) {
  for (auto& key : keys) {
    try {
      auto oid = bsoncxx::oid(data[key]);
    } catch (bsoncxx::exception &exception) {
      return false;
    }
  }
  return true;
}

std::string DataManager::UnpackOid(nlohmann::json &data, std::vector<std::string> keys) {
  for (auto& key : keys) {
    if (data.find(key) != data.end()) {
      data[key] = data[key]["$oid"];
    }
  }
  return data.dump();
}

void DataManager::WriteNotRequiredParameters(const nlohmann::json &data, nlohmann::json &result, std::vector<std::string> keys) {
  for (auto& key : keys) {
    if (data.find(key) != data.end()) {
      result[key] = data[key];
    }
  }
}
