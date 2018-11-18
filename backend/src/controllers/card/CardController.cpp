//
// Created by dpudov on 08.11.18.
//

#include "CardController.h"


void CardController::initRestOpHandlers() {
    _listener.support(web::http::methods::GET, std::bind(&CardController::handleGet, this, std::placeholders::_1));
    _listener.support(web::http::methods::POST, std::bind(&CardController::handlePost, this, std::placeholders::_1));
}

void CardController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "card" && path[1] == "get") {
            // TODO: get model from db
            int id = 1;
            int questId = 1;
            utility::string_t title = "title";
            utility::string_t imagePath = "imagePath";
            utility::string_t description = "description";
            utility::string_t type = "choose";
            auto response = web::json::value::object();
            response["id"] = id;
            response["questId"] = questId;
            response["title"] = web::json::value::string(title);
            response["imagePath"] = web::json::value::string(imagePath);
            response["description"] = web::json::value::string(description);
            response["type"] = web::json::value::string(type);
            message.reply(web::http::status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "list") {
            // TODO: get model from db

            auto response = web::json::value::object();
//            auto cards = json::array();
            message.reply(web::http::status_codes::OK, response);

        } else {
            auto response = web::json::value::object();
            response["code"] = 400;
            response["message"] = web::json::value::string("GET request to CardController is not valid!");
            message.reply(web::http::status_codes::BadRequest, response);
        }
    } else {
        auto response = web::json::value::object();
        response["code"] = 400;
        response["message"] = web::json::value::string("GET request to CardController is empty!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

void CardController::handlePost(web::http::http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "card" && path[1] == "add") {
            // TODO: get model from db
            int id = 1;
            int questId = 1;
            utility::string_t title = "title";
            utility::string_t imagePath = "imagePath";
            utility::string_t description = "description";
            utility::string_t type = "choose";
            auto response = web::json::value::object();
            response["id"] = id;
            response["questId"] = questId;
            response["title"] = web::json::value::string(title);
            response["imagePath"] = web::json::value::string(imagePath);
            response["description"] = web::json::value::string(description);
            response["type"] = web::json::value::string(type);
            message.reply(web::http::status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "edit") {
            // TODO: get model from db

            auto response = web::json::value::object();
//            auto cards = json::array();
            message.reply(web::http::status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "remove") {

            // TODO: remove model from db
            auto response = web::json::value::object();
            message.reply(web::http::status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "do_answer") {

            auto response = web::json::value::object();
            message.reply(web::http::status_codes::OK, response);

        } else if (path[0] == "card" && path[1] == "links_upsert") {

            auto response = web::json::value::object();
            message.reply(web::http::status_codes::OK, response);

        } else {
            auto response = web::json::value::object();
            response["code"] = 400;
            response["message"] = web::json::value::string("POST request to CardController is not valid!");
            message.reply(web::http::status_codes::BadRequest, response);
        }
    } else {
        auto response = web::json::value::object();
        response["code"] = 400;
        response["message"] = web::json::value::string("POST request to CardController is empty!");
        message.reply(web::http::status_codes::BadRequest, response);
    }
}

web::json::value CardController::responseNotImpl(const web::http::method &method) {
    auto response = web::json::value::object();
    response["controller"] = web::json::value::string("CardController");
    response["http_method"] = web::json::value::string(method);
    return response;
}
