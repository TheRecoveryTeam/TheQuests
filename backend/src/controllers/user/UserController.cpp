//
// Created by dpudov on 12.11.18.
//

#include "UserController.h"
#include "../NetworkUtils.h"
#include "../../user/model_manager/UserModelManager.h"
#include "../../utils/converters/ConvertNlohmannToWebJSON.h"

void UserController::InitHandlers() {
    _listener.support([this](const web::http::http_request &message) {
        std::wcout << "USER CONTROLLER" << std::endl;
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
            response["message"] = web::json::value::string("Request to UserController is not valid!");
            message.reply(web::http::status_codes::BadRequest, response);
        }
    });
    for (auto &entry : _routingEntries) {
        std::wcout << entry.url.c_str() << std::endl;
    }
}


void UserController::PasswordEdit(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void UserController::Login(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;

        auto resp = nlohmann::json::parse(manager.Login(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void UserController::Logout(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Logout(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void UserController::EditUser(web::http::http_request message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        // TODO: Call db
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void UserController::CreateUser(const web::http::http_request& message) {

    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void UserController::FindEmail(const web::http::http_request& message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        bool contains = manager.Contains(requestArgs.dump());

        auto status = contains
                ? web::http::status_codes::OK
                : web::http::status_codes::NotFound;
        nlohmann::json resp = {};

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void UserController::FindNickname(const web::http::http_request& message) {
    requestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        UserModelManager::UserModelManager manager;
        bool contains = manager.Contains(requestArgs.dump());

        auto status = contains
                      ? web::http::status_codes::OK
                      : web::http::status_codes::NotFound;
        nlohmann::json resp = {};

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void UserController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("create"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, CreateUser)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("login"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, Login)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("logout"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, Logout)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, EditUser)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("password_edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, PasswordEdit)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("find_email"),
            web::http::methods::GET,
            ASSIGN_HANDLER(UserController, FindEmail)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("find_nickname"),
            web::http::methods::GET,
            ASSIGN_HANDLER(UserController, FindNickname)
    });
}