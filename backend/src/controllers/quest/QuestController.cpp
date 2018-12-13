//
// Created by dpudov on 12.11.18.
//

#include "QuestController.h"
#include "../NetworkUtils.h"
#include "../../../src/quest/model_manager/QuestModelManager.h"

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
                QuestModelManager::QuestModelManager manager;
                //TODO: call create from DB
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    //TODO: response logic
                }
            } else {
                throw std::exception();
            }
        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("quest Create is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void QuestController::DestroyQuest(web::http::http_request message) {
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
                QuestModelManager::QuestModelManager manager;
                //TODO: call destroy from DB
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    //TODO: response logic
                }
            } else {
                throw std::exception();
            }
        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("quest Destroy is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void QuestController::EditQuest(web::http::http_request message) {
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
                QuestModelManager::QuestModelManager manager;
                //TODO: call edit from DB
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    //TODO: response logic
                }
            } else {
                throw std::exception();
            }
        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("quest Edit is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void QuestController::EditQuestImage(web::http::http_request message) {
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
                QuestModelManager::QuestModelManager manager;
                //TODO: call edit_image from DB
                std::string db_response = manager.Create(body.as_string());
                auto data = nlohmann::json::parse(db_response);;
                if (data.find("error") != data.end()) {
                    response["message"] = web::json::value::string(data["error"].get<std::string>());
                    status_code = web::http::status_codes::NotFound;
                } else {
                    //TODO: response logic
                }
            } else {
                throw std::exception();
            }
        }
        catch (std::exception const &e) {
            std::wcout << e.what() << std::endl;
            response["message"] = web::json::value::string("quest EditImage is wrong");
            status_code = web::http::status_codes::BadRequest;
        }
    };

    message
            .extract_json()
            .then(processRequest)
            .wait();
    message.reply(status_code, response);
}

void QuestController::GetQuest(web::http::http_request message) {
    auto path = requestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("detail?id=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
        std::string id_str = std::string(what[1].first, what[1].second);
        int id = std::stoi(id_str);

        auto request = web::json::value::object();
        request["id"] = id;

        auto model = QuestModelManager::QuestModelManager();
//        auto item = networkhelper::from_string(model.Get(request.as_string()));
//
//        int questId = std::stoi(item["questId"].as_string());
//        response["id"] = id;
//        response["questId"] = questId;
//        response["title"] = item["title"];
//        response["imagePath"] = item["imagePath"];
//        response["description"] = item["description"];
//        response["type"] = item["type"];
//        response["links"] = item["links"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["message"] = web::json::value::string("quest Detail is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void QuestController::Resources(web::http::http_request message) {
    auto path = requestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("resources?id=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
        std::string id_str = std::string(what[1].first, what[1].second);
        int id = std::stoi(id_str);

        auto request = web::json::value::object();
        request["id"] = id;

        auto model = QuestModelManager::QuestModelManager();
//        auto item = networkhelper::from_string(model.Get(request.as_string()));
//
//        int questId = std::stoi(item["questId"].as_string());
//        response["id"] = id;
//        response["questId"] = questId;
//        response["title"] = item["title"];
//        response["imagePath"] = item["imagePath"];
//        response["description"] = item["description"];
//        response["type"] = item["type"];
//        response["links"] = item["links"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["message"] = web::json::value::string("quest Resources is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void QuestController::List(web::http::http_request message) {
    auto path = requestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("get?page=(\\d)&limit=(\\d)&authorId=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
//        std::string id_str = std::string(what[1].first, what[1].second);
//        int id = std::stoi(id_str);
//
//        auto request = web::json::value::object();
//        request["id"] = id;

        auto model = QuestModelManager::QuestModelManager();
//        auto item = networkhelper::from_string(model.Get(request.as_string()));
//
//        int questId = std::stoi(item["questId"].as_string());
//        response["id"] = id;
//        response["questId"] = questId;
//        response["title"] = item["title"];
//        response["imagePath"] = item["imagePath"];
//        response["description"] = item["description"];
//        response["type"] = item["type"];
//        response["links"] = item["links"];

        message.reply(web::http::status_codes::OK, response);
    } else {
        response["message"] = web::json::value::string("quest List is wrong");
        message.reply(web::http::status_codes::BadRequest, response);
    }
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
