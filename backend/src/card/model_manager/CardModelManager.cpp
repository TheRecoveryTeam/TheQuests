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

CardModelManager::CardModelManager::CardModelManager() {
    auto client = MongoAccess::MongoAccess::instance().get_connection();
    collection_ = (*client)["testdb"]["Card"];
    quest_manager_ = new QuestModelManager::QuestModelManager();
    cardlink_manager_ = new CardLinkModelManager::CardLinkModelManager();
    history_manager_ = new HistoryModelManager::HistoryModelManager();
}

std::string CardModelManager::CardModelManager::get(const std::string &request) {
    auto data = nlohmann::json::parse(request);
    if (data.find("cardId") != data.end()) {
        std::string id = data["cardId"];
        try {
            auto oid = bsoncxx::oid(id);
        } catch (bsoncxx::exception &exception) {
            return nlohmann::json({{"error", "Incorrect id"}}).dump();
        }
        auto query = bsoncxx::builder::stream::document{}
                << "_id" << bsoncxx::oid(id)
                << bsoncxx::builder::stream::finalize;
        bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(query.view());
        if (result) {
            return bsoncxx::to_json(*result);
        }
        return nlohmann::json({{"error", "CardDoesNotExist"}}).dump();
    }
    return nlohmann::json({{"error", "NotEnoughData"}}).dump();
}

std::string CardModelManager::CardModelManager::create(const std::string &request) {
    auto data = nlohmann::json::parse(request);
    if (data.find("questId") == data.end() || data.find("title") == data.end() || data.find("type") == data.end()) {
        return nlohmann::json({{"error", "NotEnoughData"}}).dump();
    }
    nlohmann::json query;
    std::string quest_id = data["questId"];
    try {
        auto quest_oid = bsoncxx::oid(quest_id);
    } catch (bsoncxx::exception &exception) {
        return nlohmann::json({{"error", "Incorrect id"}}).dump();
    }
    auto quest = nlohmann::json::parse(quest_manager_->get(nlohmann::json({{"id", quest_id}}).dump()));
    if (quest.find("error") != quest.end()) {
        return nlohmann::json({{"error", "QuestDoesNotExist"}}).dump();
    }
    query["questId"] = data["questId"];
    query["title"] = data["title"];
    query["type"] = data["type"];
    if (data.find("imagePath") != data.end()) {
        query["imagePath"] = data["imagePath"];
    }
    if (data.find("description") != data.end()) {
        query["description"] = data["description"];
    }
    if (data.find("links") != data.end()) {
        query["links"] = data["links"];
    }
    bsoncxx::stdx::optional<mongocxx::result::insert_one>
            result = collection_.insert_one((bsoncxx::from_json(query.dump()).view()));
    if (result) {
        return nlohmann::json({{"_id", (*result).inserted_id().get_oid().value.to_string()}}).dump();
    } else {
        return nlohmann::json({{"error", "CreationError"}}).dump();
    }
}

std::string CardModelManager::CardModelManager::get_next_card(const std::string &request) {
    auto data = nlohmann::json::parse(request);
    if (data.find("cardId") == data.end() || data.find("answer") == data.end() || data.find("userId") == data.end()) {
        return nlohmann::json({{"error", "NotEnoughData"}}).dump();
    }
    std::string answer = data["answer"];
    auto query = bsoncxx::builder::stream::document{}
            << "_id" << bsoncxx::oid(data["cardId"])
            << bsoncxx::builder::stream::finalize;
    mongocxx::options::find opts{};
    opts.projection(
            bsoncxx::builder::stream::document{} << "links" << 1 << "questId" << 1
                                                 << bsoncxx::builder::stream::finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> result = collection_.find_one(query.view(), opts);
    if (result && (*result).view().find("links") != (*result).view().end()) {
        auto card = nlohmann::json::parse(bsoncxx::to_json((*result)));
        auto links = card["links"];
        if (links.find(answer) != links.end()) {
            nlohmann::json card_link = nlohmann::json::parse(cardlink_manager_
                                                                     ->get(nlohmann::json(
                                                                             {{"id", links[answer]}}).dump()));
            // Осторожно! Захардкоденый юзер!
            nlohmann::json history = nlohmann::json::parse(history_manager_
                                                                   ->get(nlohmann::json({{"userId",  data["userId"]},
                                                                                         {"questId", card["questId"]}}).dump()));
            if (history.find("warning") != history.end()) {
                history = nlohmann::json::parse(history_manager_
                                                        ->create(nlohmann::json({{"userId",  data["userId"]},
                                                                                 {"questId", card["questId"]}}).dump()));
            }
            bool end_game = false;
            for (auto &resource : card_link["weight"].get<std::map<std::string, int>>()) {
                history["resources"][resource.first] = (int) history["resources"][resource.first] + resource.second;

                if ((int) history["resources"][resource.first] <= 0) {
                    history["resources"][resource.first] = 0;
                    end_game = true;
                } else if ((int) history["resources"][resource.first] >= 100) {
                    history["resources"][resource.first] = 100;
                    end_game = true;
                }
            }
            std::string next_card_id;
            nlohmann::json next_card = nlohmann::json::parse(
                    get(nlohmann::json({{"cardId", card_link["toId"]}}).dump()));
            if (end_game || next_card["type"] == "finish") {
                nlohmann::json query_history_update = {
                        {"id",        history["id"]},
                        {"cardId",    ""},
                        {"resources", history["resources"]},
                        {"stage",     "end"}
                };
                if (!end_game) {
                    query_history_update["cardId"] = card_link["toId"];
                } else {
                    auto loss_card_id =
                            nlohmann::json::parse(
                                    quest_manager_->get(nlohmann::json({{"id", card["questId"]}}).dump()));
                    query_history_update["cardId"] = loss_card_id["lossCardId"];
                }
                nlohmann::json update_result = history_manager_->update(query_history_update.dump());
                if (update_result.find("error") != update_result.end()) {
                    return update_result;
                }
                next_card = query_history_update["cardId"];
            } else {
                nlohmann::json query_history_update = {
                        {"id",        history["id"]},
                        {"cardId",    card_link["toId"]},
                        {"resources", history["resources"]}
                };
                nlohmann::json update_result = history_manager_->update(query_history_update.dump());
                if (update_result.find("error") != update_result.end()) {
                    return update_result;
                }
                next_card = query_history_update["cardId"];
            }
            return nlohmann::json({
                                          {"nextCardId", next_card},
                                          {"resources",  history["resources"]}
                                  }).dump();
        } else {
            return nlohmann::json({{"error", "LinkDoesNotExist"}}).dump();
        }
    } else {
        return nlohmann::json({{"error", "CardDoesNotExist"}}).dump();
    }
}