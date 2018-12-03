//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"
#include "../NetworkUtils.h"
#include "../../../src/card/model_manager/CardModelManager.h"

web::json::value from_string(std::string const &input) {
    utility::stringstream_t s;

    s << input;
    web::json::value ret = web::json::value::parse(s);
    return ret;
}

void CardController::initRestOpHandlers() {
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

web::json::value CardController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("CardController");
    response["http_method"] = web::json::value::string(method);
    return response;
}

void CardController::add(const web::http::http_request message) {
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
                CardModelManager::CardModelManager manager;
                std::string db_response = manager.create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e)
        {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card add is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void CardController::links_upsert(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("id"));
            web::json::value questId = body.at(U("links"));

            //TODO: Links upsert from DB
            message.reply(web::http::status_codes::OK, response);
        }
        catch (web::json::json_exception &e) {
            response["code"] = 400;
            response["message"] = web::json::value::string("card links upsert is wrong");
            message.reply(web::http::status_codes::BadRequest, response);
        }

    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card links upsert is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::edit(web::http::http_request message) {
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
                CardModelManager::CardModelManager manager;
                //TODO: call edit from DB
                std::string db_response = manager.create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    response["id"] = web::json::value::string(data["id"].get<std::string>());
                }
            } else {
                throw std::exception();
            }

        }
        catch (std::exception const &e)
        {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card edit is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void CardController::remove(web::http::http_request message) {
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
                CardModelManager::CardModelManager manager;
                std::string db_response = manager.remove(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                }
            } else {

                throw std::exception();
            }

        }
        catch (std::exception const &e)
        {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card remove is wrong!");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void CardController::do_answer(web::http::http_request message) {
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
                CardModelManager::CardModelManager manager;
                //TODO: call do_answer from DB
                std::string db_response = manager.get(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    response["nextCardId"] = web::json::value::string(data["nextCardId"].get<std::string>());
                    response["resources"] = web::json::value::string(data["resources"].get<std::string>());
                }
            } else {
                throw std::exception();
            }

        }
        catch (std::exception const &e)
        {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("card do_answer is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void CardController::get(web::http::http_request message) {
    auto path = requestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("get?id=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
        std::string id_str = std::string(what[1].first, what[1].second);
        int id = std::stoi(id_str);

        auto request = web::json::value::object();
        request["id"] = id;

        auto model = CardModelManager::CardModelManager();
        auto item = from_string(model.get(request.as_string()));

        int questId = std::stoi(item["questId"].as_string());
        response["id"] = id;
        response["questId"] = questId;
        response["title"] = item["title"];
        response["imagePath"] = item["imagePath"];
        response["description"] = item["description"];
        response["type"] = item["type"];
        response["links"] = item["links"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card get is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::list(web::http::http_request message) {
    auto path = requestPath(message);
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
        auto item = from_string(model.get(request.as_string()));

        int questId = std::stoi(item["questId"].as_string());
        response["id"] = questId;
        response["title"] = item["title"];
        response["imagePath"] = item["imagePath"];
        response["description"] = item["description"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card list is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("do_answer"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(CardController, do_answer)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("remove"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(CardController, remove)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(CardController, edit)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("links_upsert"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(CardController, links_upsert)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("add"),
            web::http::methods::POST,
            CPPRESTHELPER_HANDLER(CardController, add)
    });
}
