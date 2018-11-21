//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"
#include "../NetworkUtils.h"
#include "../../card/model_manager/CardModelManager.h"

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

void CardController::add(const web::http::http_request request) {
    std::wcout << "CARD CONTROLLER ADD" << std::endl;
}

void CardController::links_upsert(web::http::http_request message) {

}

void CardController::edit(web::http::http_request message) {

}

void CardController::remove(web::http::http_request message) {

}

void CardController::do_answer(web::http::http_request message) {

}

void CardController::get(web::http::http_request message) {
    auto path = requestPath(message);
    for (auto &p : path) {
        std::wcout << p.c_str() << std::endl;
    }

    auto uri = message.relative_uri().to_string();
    std::regex ex("get?cardId=(\\d)");
    std::cmatch what;
    auto response = web::json::value::object();

    if (regex_match(uri.c_str(), what, ex)) {
        std::string id_str = std::string(what[1].first, what[1].second);
        int id = std::stoi(id_str);

        auto request = web::json::value::object();
        request["cardId"] = id;

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

}


void CardController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("get"),
            web::http::methods::GET,
            CPPRESTHELPER_HANDLER(CardController, get)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("list"),
            web::http::methods::GET,
            CPPRESTHELPER_HANDLER(CardController, list)
    });

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
