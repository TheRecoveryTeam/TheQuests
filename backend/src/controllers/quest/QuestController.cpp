//
// Created by dpudov on 12.11.18.
//

#include "QuestController.h"
#include "../NetworkUtils.h"
#include "../../../src/quest/model_manager/QuestModelManager.h"
#include "../../utils/converters/ConvertNlohmannToWebJSON.h"

void QuestController::InitHandlers() {
    _listener.support([this](const web::http::http_request &message) {
        std::wcout << "QUEST CONTROLLER" << std::endl;
        std::wcout << message.relative_uri().path().c_str() << std::endl;
        bool found = false;
        for (auto &entry : _routingEntries) {
            if (message.relative_uri().path() != entry.url || message.method() != entry.method) {
                continue;
            }
            entry.handler(message);
            found = true;
            break;
        }
        if (!found) {
            auto response = web::json::value::object();
            response["code"] = 400;
            response["message"] = web::json::value::string("Request to QuestController is not valid!");
            message.reply(web::http::status_codes::BadRequest, response);
        }
    });
    for (auto &entry : _routingEntries) {
        std::wcout << entry.url.c_str() << std::endl;
    }
}

void QuestController::CreateQuest(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void QuestController::DestroyQuest(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void QuestController::EditQuest(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void QuestController::EditQuestImage(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void QuestController::GetQuest(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;

        auto resp = nlohmann::json::parse(manager.GetWithHistory(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void QuestController::Resources(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Get(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void QuestController::List(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Get(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void QuestController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("detail"),
            web::http::methods::GET,
            ASSIGN_HANDLER(QuestController, GetQuest)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("resources"),
            web::http::methods::GET,
            ASSIGN_HANDLER(QuestController, Resources)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("list"),
            web::http::methods::GET,
            ASSIGN_HANDLER(QuestController, List)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit_image"),
            web::http::methods::POST,
            ASSIGN_HANDLER(QuestController, EditQuestImage)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(QuestController, EditQuest)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("destroy"),
            web::http::methods::POST,
            ASSIGN_HANDLER(QuestController, DestroyQuest)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("create"),
            web::http::methods::POST,
            ASSIGN_HANDLER(QuestController, CreateQuest)
    });
}
