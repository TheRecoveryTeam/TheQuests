#include <bsoncxx/builder/stream/document.hpp>
#include "CardLinkModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>


std::string CardLinkModelManager::CardLinkModelManager::Get(const std::string &request,
                                                            const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::Get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"toId"};
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}