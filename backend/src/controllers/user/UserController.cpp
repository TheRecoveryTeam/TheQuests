//
// Created by dpudov on 12.11.18.
//

#include "UserController.h"

void UserController::handleGet(web::http::http_request message) {

}

void UserController::handlePost(web::http::http_request message) {

}

void UserController::initRestOpHandlers() {
    _listener.support(web::http::methods::GET, std::bind(&UserController::handleGet, this, std::placeholders::_1));
    _listener.support(web::http::methods::POST, std::bind(&UserController::handlePost, this, std::placeholders::_1));
}

web::json::value UserController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("UserController");
    response["http_method"] = web::json::value::string(method);
    return response;
}
