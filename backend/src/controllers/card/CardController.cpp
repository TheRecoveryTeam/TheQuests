//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"
#include "../NetworkUtils.h"
#include "../../storage/models/CardModel.h"

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

    auto uri = message.relative_uri();
//    boost::regex ex("get?id=//d");
//    boost::cmatch what;

    int id = message.relative_uri();
    int questId = 1;
    utility::string_t title = "title";
    utility::string_t imagePath = "imagePath";
    utility::string_t description = "description";
    utility::string_t type = "choose";

    auto response = web::json::value::object();
    auto model = CardModel::CardModel(response.serialize());
    auto item = model.get();

    response["id"] = id;
    response["questId"] = questId;
    response["title"] = web::json::value::string(title);
    response["imagePath"] = web::json::value::string(imagePath);
    response["description"] = web::json::value::string(description);
    response["type"] = web::json::value::string(type);

    message.reply(web::http::status_codes::OK, response);
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
