//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"


void CardController::initRestOpHandlers() {
    AbstractController::initRestOpHandlers();
}

void CardController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "card" && path[1] == "get") {

        } else if (path[0] == "card" && path[1] == "list") {

        } else {
            auto response = json::value::object();
            response["code"] = 400;
            response["message"] = json::value::string("GET request to CardController is not valid!");
            message.reply(status_codes::BadRequest, response);
        }
    } else {
        auto response = json::value::object();
        response["code"] = 400;
        response["message"] = json::value::string("GET request to CardController is empty!");
        message.reply(status_codes::BadRequest, response);
    }
}

void CardController::handlePost(http_request message) {

}

json::value CardController::responseNotImpl(const http::method &method) {
    auto response = json::value::object();
    response["controller"] = json::value::string("CardController");
    response["http_method"] = json::value::string(method);
    return response;
}
