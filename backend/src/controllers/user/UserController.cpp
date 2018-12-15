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


void UserController::password_edit(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();

    auto status_code = web::http::status_codes::OK;
    auto processRequest = [&response, &status_code, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty() || body.is_null()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            UserModelManager::UserModelManager manager;
            std::string db_response = manager.Create(body.as_string());
            auto data = nlohmann::json::parse(db_response);;
            if (data.find("error") != data.end()) {
                response["message"] = web::json::value::string(data["error"].get<std::string>());
                response["nicknameError"] = web::json::value::string(data["nicknameError"].get<std::string>());
                status_code = web::http::status_codes::NotFound;
            } else {
                response["id"] = web::json::value::string(data["id"].get<std::string>());
                response["token"] = web::json::value::string(data["token"].get<std::string>());
            }
        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("user logout is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();

    message.reply(status_code, response);
}

void UserController::create(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();

    auto status_code = web::http::status_codes::OK;
    auto processRequest = [&response, &status_code, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                UserModelManager::UserModelManager manager;
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                    response["token"] = web::json::value::string(data["token"].get<std::string>());
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("user CreateQuest is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void UserController::login(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();

    auto status_code = web::http::status_codes::OK;
    auto processRequest = [&response, &status_code, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                UserModelManager::UserModelManager manager;
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    response["passwordError"] = web::json::value::string(data["passwordError"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                    response["email"] = web::json::value::string(data["email"].get<std::string>());
                    response["nickname"] = web::json::value::string(data["nickname"].get<std::string>());
                    response["token"] = web::json::value::string(data["token"].get<std::string>());
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("user login is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void UserController::logout(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();

    auto status_code = web::http::status_codes::OK;
    auto processRequest = [&response, &status_code, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                UserModelManager::UserModelManager manager;
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("user logout is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void UserController::edit(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();

    auto status_code = web::http::status_codes::OK;
    auto processRequest = [&response, &status_code, path](pplx::task<web::json::value> task) {

        try {
            auto const &body = task.get();
            if (path.empty()) {
                throw std::exception();
            }
            std::wcout << body.as_string().c_str() << std::endl;
            if (!body.is_null()) {
                UserModelManager::UserModelManager manager;
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    response["nicknameError"] = web::json::value::string(data["nicknameError"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("user logout is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void UserController::find_nickname(web::http::http_request message) {

}

void UserController::find_email(web::http::http_request message) {

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
            ASSIGN_HANDLER(UserController, login)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("logout"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, logout)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, edit)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("password_edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(UserController, password_edit)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("find_email"),
            web::http::methods::GET,
            ASSIGN_HANDLER(UserController, FindEmail)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("find_nickname"),
            web::http::methods::GET,
            ASSIGN_HANDLER(UserController, find_nickname)
    });
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

