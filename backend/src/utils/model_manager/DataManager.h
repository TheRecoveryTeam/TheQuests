#ifndef THEQUESTS_DATAMANAGER_H
#define THEQUESTS_DATAMANAGER_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>


namespace DataManager {
  bool CheckRequiredParameters(const nlohmann::json &data, std::vector<std::string> keys);
  bool CheckIdCorrectness(const nlohmann::json &data, std::vector<std::string> keys);
  std::string UnpackOid(nlohmann::json &data, std::vector<std::string> keys);
  void WriteNotRequiredParameters(const nlohmann::json &data, nlohmann::json &result, std::vector<std::string> keys);
}
#endif //THEQUESTS_DATAMANAGER_H
