//
// Created by dpudov on 12.11.18.
//

#include <utils/decorators/required_args/RequiredArgsDecorator.h>
#include <utils/decorators/login_required/LoginRequiredDecorator.h>
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
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, process_logic);
}

void QuestController::DestroyQuest(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, process_logic);
}

void QuestController::EditQuest(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, process_logic);
}

void QuestController::EditQuestImage(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, process_logic);
}

void QuestController::GetQuest(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this, message](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;

        auto resp = nlohmann::json::parse(manager.GetWithHistory(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        message.reply(status, converters::ConvertNlohmannToWebJSON(resp));
    };


    auto required_auth_decorator
            = decorators::LoginRequiredDecorator(message, process_logic);
    auto required_args_decorator
            = decorators::RequiredArgsDecorator({ "id" }, message, required_auth_decorator);

    ProcessGet(message, required_args_decorator);
}

void QuestController::Resources(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Get(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, process_logic);
}

void QuestController::List(web::http::http_request message) {
    RequestLogicProcessor process_logic = [this](const nlohmann::json& request_args) {

        QuestModelManager::QuestModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Get(request_args.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, process_logic);
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
