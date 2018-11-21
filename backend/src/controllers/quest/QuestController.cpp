//
// Created by dpudov on 12.11.18.
//

#include "QuestController.h"

void QuestController::initRestOpHandlers() {
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

web::json::value QuestController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("QuestController");
    response["http_method"] = web::json::value::string(method);
    return response;
}

void QuestController::create(web::http::http_request message) {

}

void QuestController::destroy(web::http::http_request message) {

}

void QuestController::edit(web::http::http_request message) {

}

void QuestController::edit_image(web::http::http_request message) {

}

void QuestController::detail(web::http::http_request message) {

}

void QuestController::resources(web::http::http_request message) {

}

void QuestController::list(web::http::http_request message) {

}

void QuestController::ConfigureRouting() {

}
