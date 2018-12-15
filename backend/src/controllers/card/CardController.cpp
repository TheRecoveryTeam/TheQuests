//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"
#include "../NetworkUtils.h"
#include "../../../src/card/model_manager/CardModelManager.h"
#include "../../utils/converters/ConvertNlohmannToWebJSON.h"

void CardController::InitHandlers() {
    _listener.support([this](const web::http::http_request &message) {
        std::wcout << "CARD CONTROLLER" << std::endl;
        std::wcout << message.relative_uri().path().c_str() << std::endl;
        auto response = web::json::value::object();

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
            response["code"] = 400;
            response["message"] = web::json::value::string("Request to CardController is not valid!");

            message.reply(web::http::status_codes::BadRequest, response);
        }
    });
    for (auto &entry : _routingEntries) {
        std::wcout << entry.url.c_str() << std::endl;
    }
}

void CardController::AddNewCard(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::LinksUpsert(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::EditCard(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::RemoveCard(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::DoAnswer(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        auto resp = nlohmann::json::parse(manager.GetNextCard(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void CardController::GetCard(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {
        CardModelManager::CardModelManager manager;
        auto items = nlohmann::json::parse(manager.Get(requestArgs.dump()));

        auto resp_items = nlohmann::json::array();
        if (!items["links"].empty()) {
            for (auto &link : items["links"]) {
                resp_items.push_back(link);
            }
        }

        auto resp = items;
        resp["links"] = resp_items;

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void CardController::List(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {
        CardModelManager::CardModelManager manager;
        auto items = nlohmann::json::parse(manager.Get(requestArgs.dump()));
        // TODO: List from DB
        auto resp_items = nlohmann::json::array();
        if (!items["links"].empty()) {
            for (auto &link : items["links"]) {
                resp_items.push_back(link);
            }
        }

        auto resp = items;
        resp["links"] = resp_items;

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void CardController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("do_answer"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, DoAnswer)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("remove"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, RemoveCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, EditCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("links_upsert"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, LinksUpsert)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("add"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, AddNewCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("get"),
            web::http::methods::GET,
            ASSIGN_HANDLER(CardController, GetCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("list"),
            web::http::methods::GET,
            ASSIGN_HANDLER(CardController, List)
    });
}
