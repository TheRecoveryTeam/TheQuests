//
// Created by dpudov on 12.11.18.
//

#include "UserController.h"
#include "../NetworkUtils.h"

void UserController::initRestOpHandlers() {
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

void UserController::password_edit(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value password = body.at(U("password"));
            web::json::value newPassword = body.at(U("newPassword"));
            //TODO: Remove from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("user edit password is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("user edit password is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void UserController::create(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("email"));
            web::json::value password = body.at(U("password"));
            //TODO: Create from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("user create is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("user create is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void UserController::login(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("email"));
            web::json::value password = body.at(U("password"));
            //TODO: Login from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("user login is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("user login is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void UserController::logout(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("id"));
            //TODO: logout from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("user logout is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("user logout is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void UserController::edit(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("nickname"));
            //TODO: edit from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("user edit is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("user edit is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void UserController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("create"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(UserController, create)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("login"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(UserController, login)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("logout"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(UserController, logout)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(UserController, edit)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("password_edit"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(UserController, password_edit)
    });
}
