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
    auto path = RequestPath(message);
    auto response = web::json::value::object();
    auto statusCode = web::http::status_codes::OK;

    auto processRequest = [&response, &statusCode, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                CardModelManager::CardModelManager manager;
                //TODO: call links_upsert from DB
                std::string dbResponse = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(dbResponse);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    statusCode = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                }
            } else {
                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card LinksUpsertCard is wrong");
            statusCode = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(statusCode, response);
}

void CardController::EditCard(web::http::http_request message) {
    auto path = RequestPath(message);
    auto response = web::json::value::object();
    auto statusCode = web::http::status_codes::OK;

    auto processRequest = [&response, &statusCode, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                CardModelManager::CardModelManager manager;
                //TODO: call edit from DB
                std::string dbResponse = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(dbResponse);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    statusCode = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                }
            } else {
                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card EditCard is wrong");
            statusCode = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(statusCode, response);
}

void CardController::RemoveCard(web::http::http_request message) {
    auto path = RequestPath(message);
    auto response = web::json::value::object();

    auto statusCode = web::http::status_codes::OK;
    auto processRequest = [&response, &statusCode, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                CardModelManager::CardModelManager manager;
                // TODO: REMOVE IN DB NOT IMPLEMENTED
//                std::string dbResponse = manager.remove(body.as_string());
                std::string dbResponse = "{}";
                auto data = nlohmann::json::parse(dbResponse);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    statusCode = web::http::status_codes::NotFound;
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card RemoveCard is wrong!");
            statusCode = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(statusCode, response);
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
    auto path = RequestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("list?questId=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
        std::string id_str = std::string(what[1].first, what[1].second);
        int id = std::stoi(id_str);

        auto request = web::json::value::object();
        request["questId"] = id;

        auto model = CardModelManager::CardModelManager();
//        auto item = networkhelper::from_string(model.Get(request.as_string()));
//
//        int questId = std::stoi(item["questId"].as_string());
//        response["id"] = questId;
//        response["title"] = item["title"];
//        response["imagePath"] = item["imagePath"];
//        response["description"] = item["description"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["message"] = web::json::value::string("card List is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
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
