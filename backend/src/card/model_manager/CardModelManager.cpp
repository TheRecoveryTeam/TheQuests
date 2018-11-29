//
// Created by Арсений Зорин on 10/11/2018.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "CardModelManager.h"
#include <mongocxx/client.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>

CardModelManager::CardModelManager::CardModelManager() : AbstractModelManager::AbstractModelManager("Card"){
  quest_manager_ = new QuestModelManager::QuestModelManager();
  cardlink_manager_ = new CardLinkModelManager::CardLinkModelManager();
  history_manager_ = new HistoryModelManager::HistoryModelManager();
}

std::string CardModelManager::CardModelManager::get(const std::string &request, const std::vector<std::string> *projection) {
  auto result = nlohmann::json::parse(AbstractModelManager::get(request, projection));
  if (result.find("error") == result.end()) {
    std::vector<std::string> id_data = {"questId"};
    if (result.find("links") != result.end()) {
      for (auto& link : result["links"]) {
        link = link["$oid"];
      }
    }
    return DataManager::UnpackOid(result, id_data);
  }
  return result.dump();
}

std::string CardModelManager::CardModelManager::create(const std::string &request) {
  std::vector<std::string> required_data = {"questId", "title", "type"};
  std::vector<std::string> not_required_data = {"imagePath", "description", "links"};
  std::vector<std::string> id_data = {"questId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  auto quest = nlohmann::json::parse(quest_manager_->get(nlohmann::json({{"id", data["questId"]}}).dump()));
  if (quest.find("error") != quest.end()) {
    return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
  }
  nlohmann::json new_card = {
      {"questId", {{"$oid", data["questId"]}}},
      {"title", data["title"]},
      {"type", data["type"]}
  };
  if (data.find("links") != data.end()) {
    for (auto &link : data["links"].get<std::map<std::string, std::string>>()) {
      data["links"].erase(link.first);
      data["links"][link.first]["$oid"] = link.second;
    }
  }
  DataManager::WriteNotRequiredParameters(data, new_card, not_required_data);
  bsoncxx::stdx::optional<mongocxx::result::insert_one>
      result = collection_.insert_one((bsoncxx::from_json(new_card.dump()).view()));
  if (result) {
    return get(nlohmann::json({{"id", (*result).inserted_id().get_oid().value.to_string()}}).dump());
  } else {
    return nlohmann::json({{"error", "CreationError"}}).dump();
  }
}

std::string CardModelManager::CardModelManager::get_next_card(const std::string &request) {
  // Проверка корректности входных параметров
  std::vector<std::string> required_data = {"id", "userId", "answer"};
  std::vector<std::string> id_data = {"id", "userId"};
  auto data = nlohmann::json::parse(request);
  if (!DataManager::CheckRequiredParameters(data, required_data)) {
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
  }
  if (!DataManager::CheckIdCorrectness(data, id_data)) {
    return nlohmann::json({{"error", "IncorrectId"}}).dump();
  }
  // Получение QuestId и Links текущей карточки
  nlohmann::json query = {
      {"id", data["id"]}
  };
  std::vector<std::string> options = {"links", "questId"};
  auto card = nlohmann::json::parse(get(query.dump(), &options));
  // Проверка отсутствия ошибок поиска карточки и наличия Links
  if (!(card.find("error") == card.end() && card.find("links") != card.end())) {
    return nlohmann::json({{"error", "CardDoesNotExist"}}).dump();
  }
  auto links = card["links"];
  std::string answer = data["answer"];
  // Проверка присутствия полученного ответа в Links
  if (links.find(answer) == links.end()) {
    return nlohmann::json({{"error", "LinkDoesNotExist"}}).dump();
  }
  // Получение CardLink и History
  nlohmann::json card_link = nlohmann::json::parse(cardlink_manager_
                                                       ->get(nlohmann::json({{"id", links[answer]}}).dump()));
  nlohmann::json history = nlohmann::json::parse(history_manager_
                                                     ->get_user_history(nlohmann::json({{"userId", data["userId"]},
                                                                           {"questId", card["questId"]}}).dump()));
  // Если History для данного пользователя еще не создана, то добавляем ее
  if (history.find("warning") != history.end()) {
    history = nlohmann::json::parse(history_manager_
                                        ->create(nlohmann::json({{"userId", data["userId"]},
                                                                 {"questId", card["questId"]}}).dump()));
  }
  bool lose_game = false; // Флаг проигрыша игры
  // Обновление списка ресурсов
  for (auto &resource : card_link["weight"].get<std::map<std::string, int>>()) {
    history["resources"][resource.first] = (int) history["resources"][resource.first] + resource.second;
    // Проверка выхода ресурсов за границы
    if ((int) history["resources"][resource.first] <= 0) {
      history["resources"][resource.first] = 0;
      lose_game = true;
    } else if ((int) history["resources"][resource.first] >= 100) {
      history["resources"][resource.first] = 100;
      lose_game = true;
    }
  }
  // Получаем следующую карточку
  nlohmann::json query_history_update;
  // Проверка окончания игры (либо ресурсы вышли за допустимые границы, либо следующая карточка финишная
  if (lose_game || nlohmann::json::parse(get(nlohmann::json({{"id", card_link["toId"]}}).dump()))["type"] == "finish") {
    // Собираем обновленную History
    query_history_update = {
        {"id", history["id"]},
        {"resources", history["resources"]},
        {"stage", "end"}
    };
    // Если выиграли
    if (!lose_game) {
      query_history_update["cardId"] = card_link["toId"];
    } else {
      // Будьте добры пройти на карточку проигрыша
      auto loss_card_id =
          nlohmann::json::parse(quest_manager_->get(nlohmann::json({{"id", card["questId"]}}).dump()));
      query_history_update["cardId"] = loss_card_id["lossCardId"];
    }
  } else { // Продолжаем играть, если с ресурсами все хорошо и еще не конец
    query_history_update = {
        {"id", history["id"]},
        {"cardId", card_link["toId"]},
        {"resources", history["resources"]}
    };
  }
  // Обновляем History
  nlohmann::json update_result = history_manager_->update(query_history_update.dump());
  if (update_result.find("error") != update_result.end()) {
    return update_result;
  }
  std::string next_card_id = query_history_update["cardId"];
  return nlohmann::json({
                            {"nextCardId", next_card_id},
                            {"resources", history["resources"]}
                        }).dump();
}
