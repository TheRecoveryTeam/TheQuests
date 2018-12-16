//
// Created by dpudov on 12.11.18.
//

#include <cpprest/http_client.h>
#include <utils/decorators/required_args/RequiredArgsDecorator.h>
#include <utils/decorators/login_required/LoginRequiredDecorator.h>
#include <utils/converters/ConvertNlohmannToWebJSON.h>
#include <user/model_manager/UserModelManager.h>
#include "UserController.h"
#include "../NetworkUtils.h"

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
            response["code"] = 400;
            response["message"] = web::json::value::string("Request to UserController is not valid!");
            message.reply(web::http::status_codes::BadRequest, response);
        }
    });
    for (auto &entry : _routingEntries) {
        std::wcout << entry.url.c_str() << std::endl;
    }
}

web::json::value UserController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("UserController");
    response["http_method"] = web::json::value::string(method);
    return response;
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
            ASSIGN_HANDLER(UserController, LoginUser)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("logout"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, LogoutUser)
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

void UserController::CreateUser(const web::http::http_request& message) {

    RequestLogicProcessor process_logic = [this, message](const nlohmann::json& request_args) {

        UserModelManager::UserModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(request_args.dump()));

        auto status = ValidateManagerResponse(resp);

        message.reply(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    auto required_args_decorator
        = decorators::RequiredArgsDecorator({ "email", "nickname", "password" },
                message, process_logic);

    ProcessPost(message, process_logic);
}

void UserController::FindEmail(const web::http::http_request& message) {
    RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {

        UserModelManager::UserModelManager manager;
        bool contains = manager.Contains(request_args.dump());

        auto status = contains
                ? web::http::status_codes::OK
                : web::http::status_codes::NotFound;

        message.reply(status);
    };

    auto required_args_decorator
        = decorators::RequiredArgsDecorator({ "email" }, message, process_logic);

    ProcessGet(message, required_args_decorator);
}

void UserController::FindNickname(const web::http::http_request& message) {
    RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {
        UserModelManager::UserModelManager manager;
        bool contains = manager.Contains(request_args.dump());

        auto status = contains
                      ? web::http::status_codes::OK
                      : web::http::status_codes::NotFound;

        message.reply(status);
    };

    auto required_args_decorator
        = decorators::RequiredArgsDecorator({ "nickname" }, message, process_logic);

    ProcessGet(message, required_args_decorator);
}

void UserController::LoginUser(const web::http::http_request& message) {

    RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {
        UserModelManager::UserModelManager manager;
        auto resp = nlohmann::json::parse(manager.Login(request_args.dump()));

        auto status = ValidateManagerResponse(resp);
        message.reply(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    auto required_args_decorator
        = decorators::RequiredArgsDecorator({ "email", "password" }, message, process_logic);

    ProcessPost(message, required_args_decorator);
}

void UserController::LogoutUser(const web::http::http_request& message) {

    RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {
        UserModelManager::UserModelManager manager;

        manager.Logout(request_args.dump());

        message.reply(web::http::status_codes::OK);
    };

    auto login_required_decorator
        = decorators::LoginRequiredDecorator(message, process_logic);

    ProcessPost(message, login_required_decorator);
}
