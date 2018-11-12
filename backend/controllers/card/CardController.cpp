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
            // TODO: get model from db
            int id = 1;
            int questId = 1;
            string_t title = "title";
            string_t imagePath = "imagePath";
            string_t description = "description";
            string_t type = "choose";
            auto response = json::value::object();
            response["id"] = id;
            response["questId"] = questId;
            response["title"] = json::value::string(title);
            response["imagePath"] = json::value::string(imagePath);
            response["description"] = json::value::string(description);
            response["type"] = json::value::string(type);
            message.reply(status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "list") {
            // TODO: get model from db

            auto response = json::value::object();
//            auto cards = json::array();
            message.reply(status_codes::OK, response);

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
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "card" && path[1] == "add") {
            // TODO: get model from db
            int id = 1;
            int questId = 1;
            string_t title = "title";
            string_t imagePath = "imagePath";
            string_t description = "description";
            string_t type = "choose";
            auto response = json::value::object();
            response["id"] = id;
            response["questId"] = questId;
            response["title"] = json::value::string(title);
            response["imagePath"] = json::value::string(imagePath);
            response["description"] = json::value::string(description);
            response["type"] = json::value::string(type);
            message.reply(status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "list") {
            // TODO: get model from db

            auto response = json::value::object();
//            auto cards = json::array();
            message.reply(status_codes::OK, response);

        } else {
            auto response = json::value::object();
            response["code"] = 400;
            response["message"] = json::value::string("POST request to CardController is not valid!");
            message.reply(status_codes::BadRequest, response);
        }
    } else {
        auto response = json::value::object();
        response["code"] = 400;
        response["message"] = json::value::string("POST request to CardController is empty!");
        message.reply(status_codes::BadRequest, response);
    }
}

json::value CardController::responseNotImpl(const http::method &method) {
    auto response = json::value::object();
    response["controller"] = json::value::string("CardController");
    response["http_method"] = json::value::string(method);
    return response;
}
