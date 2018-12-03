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
    if (!path.empty()) {
        auto status_code = web::http::status_codes::OK;
        message
                .extract_json()
                .then([&response, &status_code](pplx::task<web::json::value> task) {

                    try {
                        auto const &body = task.get();
                        std::wcout << body.as_string().c_str() << std::endl;
                        if (!body.is_null()) {
                            web::json::value id = body.at(U("id"));
                            web::json::value questId = body.at(U("questId"));
                            web::json::value title = body.at(U("title"));
                            web::json::value description = body.at(U("description"));
                            web::json::value type = body.at(U("type"));
                            nlohmann::json new_card = {
                                    {"questId",     questId.as_string()},
                                    {"title",       title.as_string()},
                                    {"description", description.as_string()},
                                    {"type",        type.as_string()},
                            };

                            CardModelManager::CardModelManager manager;
                            std::string db_response = manager.create(new_card.dump());
                            auto data = nlohmann::json::parse(db_response);;
                            if (data.find("error") != data.end()) {
                                response["code"] = 404;
                                response["message"] = web::json::value::string(data["error"].get<std::string>());
                                status_code = web::http::status_codes::NotFound;
                            } else {
                                response["id"] = web::json::value::string(data["id"].get<std::string>());
                            }
                        } else {
                            std::wcout << "Empty response received." << std::endl;
                            response["code"] = 400;
                            response["message"] = web::json::value::string("card add is wrong");

                        }

                    } catch (web::http::http_exception const &e) {
                        std::wcout << e.what() << std::endl;
                        response["code"] = 400;
                        response["message"] = web::json::value::string("card add is wrong");
                    } catch (std::exception const &e)
                    {
                        std::wcout << e.what() << std::endl;
                    }
                })
                .wait();
        message.reply(status_code, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card add is wrong");
        response["description"] = web::json::value::string("Empty path!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::links_upsert(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto body = message.extract_json().get();
        try {
            web::json::value id = body.at(U("id"));
            web::json::value questId = body.at(U("links"));

            //TODO: Edit from DB
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
    if (!path.empty()) {
        auto status_code = web::http::status_codes::OK;
        message
                .extract_json()
                .then([&response, &status_code](pplx::task<web::json::value> task) {

                    try {
                        auto const &body = task.get();
                        std::wcout << body.as_string().c_str() << std::endl;
                        if (!body.is_null()) {
                            web::json::value id = body.at(U("id"));
                            web::json::value questId = body.at(U("questId"));
                            web::json::value title = body.at(U("title"));
                            web::json::value description = body.at(U("description"));
                            web::json::value type = body.at(U("type"));
                            nlohmann::json new_card = {
                                    {"questId",     questId.as_string()},
                                    {"title",       title.as_string()},
                                    {"description", description.as_string()},
                                    {"type",        type.as_string()},
                            };

                            CardModelManager::CardModelManager manager;
                            //TODO: call edit from DB
                            std::string db_response = manager.create(new_card.dump());
                            auto data = nlohmann::json::parse(db_response);;
                            if (data.find("error") != data.end()) {
                                response["code"] = 404;
                                response["message"] = web::json::value::string(data["error"].get<std::string>());
                                status_code = web::http::status_codes::NotFound;
                            } else {
                                response["id"] = web::json::value::string(data["id"].get<std::string>());
                            }
                        } else {
                            std::wcout << "Empty response received." << std::endl;
                            response["code"] = 400;
                            response["message"] = web::json::value::string("card edit is wrong");

                        }

                    } catch (web::http::http_exception const &e) {
                        std::wcout << e.what() << std::endl;
                        response["code"] = 400;
                        response["message"] = web::json::value::string("card edit is wrong");
                    } catch (std::exception const &e)
                    {
                        std::wcout << e.what() << std::endl;
                    }
                })
                .wait();
        message.reply(status_code, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card edit is wrong");
        response["description"] = web::json::value::string("Empty path!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::remove(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto status_code = web::http::status_codes::OK;
        message
                .extract_json()
                .then([&response, &status_code](pplx::task<web::json::value> task) {

                    try {
                        auto const &body = task.get();
                        std::wcout << body.as_string().c_str() << std::endl;
                        if (!body.is_null()) {
                            web::json::value id = body.at(U("id"));
                            nlohmann::json new_card = {
                                    {"questId",     id.as_string()},
                            };

                            CardModelManager::CardModelManager manager;
                            std::string db_response = manager.remove(new_card.dump());
                            auto data = nlohmann::json::parse(db_response);
                            if (data.find("error") != data.end()) {
                                response["code"] = 404;
                                response["message"] = web::json::value::string(data["error"].get<std::string>());
                                status_code = web::http::status_codes::NotFound;
                            }
                        } else {
                            std::wcout << "Empty response received." << std::endl;
                            response["code"] = 400;
                            response["message"] = web::json::value::string("card remove is wrong");

                        }

                    } catch (web::http::http_exception const &e) {
                        std::wcout << e.what() << std::endl;
                        response["code"] = 400;
                        response["message"] = web::json::value::string("card remove is wrong");
                    } catch (std::exception const &e)
                    {
                        std::wcout << e.what() << std::endl;
                    }
                })
                .wait();
        message.reply(status_code, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card remove is wrong");
        response["description"] = web::json::value::string("Empty path!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::do_answer(web::http::http_request message) {
    auto path = requestPath(message);
    auto response = web::json::value::object();
    if (!path.empty()) {
        auto status_code = web::http::status_codes::OK;
        message
                .extract_json()
                .then([&response, &status_code](pplx::task<web::json::value> task) {

                    try {
                        auto const &body = task.get();
                        std::wcout << body.as_string().c_str() << std::endl;
                        if (!body.is_null()) {
                            web::json::value id = body.at(U("id"));
                            web::json::value ans = body.at(U("answer"));
                            nlohmann::json new_card = {
                                    {"questId",     id.as_string()},
                                    {"answer",      ans.as_string()},
                            };

                            CardModelManager::CardModelManager manager;
                            std::string db_response = manager.get(new_card.dump());
                            auto data = nlohmann::json::parse(db_response);
                            if (data.find("error") != data.end()) {
                                response["code"] = 404;
                                response["message"] = web::json::value::string(data["error"].get<std::string>());
                                status_code = web::http::status_codes::NotFound;
                            } else {
                                response["nextCardId"] = web::json::value::string(data["nextCardId"].get<std::string>());
                                response["resources"] = web::json::value::string(data["resources"].get<std::string>());
                            }
                        } else {
                            std::wcout << "Empty response received." << std::endl;
                            response["code"] = 400;
                            response["message"] = web::json::value::string("card do_answer is wrong");
                        }

                    } catch (web::http::http_exception const &e) {
                        std::wcout << e.what() << std::endl;
                        response["code"] = 400;
                        response["message"] = web::json::value::string("card do_answer is wrong");
                    } catch (std::exception const &e)
                    {
                        std::wcout << e.what() << std::endl;
                    }
                })
                .wait();
        message.reply(status_code, response);
    } else {
        response["code"] = 400;
        response["message"] = web::json::value::string("card remove is wrong");
        response["description"] = web::json::value::string("Empty path!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
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
