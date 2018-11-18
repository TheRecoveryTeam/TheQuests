//
// Created by dpudov on 12.11.18.
//

#include "UserController.h"

void UserController::handleGet(http_request message) {

}

void UserController::handlePost(http_request message) {

}

void UserController::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&UserController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&UserController::handlePost, this, std::placeholders::_1));
}

json::value UserController::responseNotImpl(const http::method &method) {
    auto response = json::value::object();
    response["controller"] = json::value::string("UserController");
    response["http_method"] = json::value::string(method);
    return response;
}
