//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"

void CardController::initRestOpHandlers() {
    _listener.support(web::http::methods::GET, std::bind(&CardController::handleGet, this, std::placeholders::_1));
    _listener.support(web::http::methods::POST, std::bind(&CardController::handlePost, this, std::placeholders::_1));
}

void CardController::handleGet(web::http::http_request message) {
    if (_cardRouter.isValid(message)) {
        _cardRouter.route_get_request(message);
    } else {
        auto response = web::json::value::object();
        response["code"] = 400;
        response["message"] = web::json::value::string("GET request to CardController is not valid!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::handlePost(web::http::http_request message) {
    if (_cardRouter.isValid(message)) {
        _cardRouter.route_post_request(message);
    } else {
        auto response = web::json::value::object();
        response["code"] = 400;
        response["message"] = web::json::value::string("POST request to CardController is not valid!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

web::json::value CardController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("CardController");
    response["http_method"] = web::json::value::string(method);
    return response;
}
