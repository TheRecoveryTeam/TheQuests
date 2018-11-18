//
// Created by dpudov on 12.11.18.
//

#include "QuestController.h"

void QuestController::handleGet(web::http::http_request message) {

}

void QuestController::handlePost(web::http::http_request message) {

}

void QuestController::initRestOpHandlers() {
    _listener.support(web::http::methods::GET, std::bind(&QuestController::handleGet, this, std::placeholders::_1));
    _listener.support(web::http::methods::POST, std::bind(&QuestController::handlePost, this, std::placeholders::_1));
}

web::json::value QuestController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("QuestController");
    response["http_method"] = web::json::value::string(method);
    return response;
}
