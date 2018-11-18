//
// Created by dpudov on 12.11.18.
//

#include "QuestController.h"

void QuestController::handleGet(http_request message) {

}

void QuestController::handlePost(http_request message) {

}

void QuestController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&QuestController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&QuestController::handlePost, this, std::placeholders::_1));
}

json::value QuestController::responseNotImpl(const http::method &method) {
    auto response = json::value::object();
    response["controller"] = json::value::string("QuestController");
    response["http_method"] = json::value::string(method);
    return response;
}
