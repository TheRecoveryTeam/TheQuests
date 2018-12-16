//
// Created by dpudov on 08.11.18.
//


#include <card/controller/CardController.h>
#include <utils/controller/NetworkUtils.h>
#include <card/model_manager/CardModelManager.h>
#include <utils/converters/ConvertNlohmannToWebJSON.h>
#include <utils/decorators/required_args/RequiredArgsDecorator.h>
#include <utils/decorators/login_required/LoginRequiredDecorator.h>

const std::string USER_ID = "user_id";

void CardController::InitHandlers() {
    _listener.support([this](const web::http::http_request &message) {
        std::wcout << "CARD CONTROLLER" << std::endl;
        std::wcout << message.relative_uri().path().c_str() << std::endl;
        auto response = web::json::value::object();

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
            response["code"] = 400;
            response["message"] = web::json::value::string("Request to CardController is not valid!");

            message.reply(web::http::status_codes::BadRequest, response);
        }
    });
    for (auto &entry : _routingEntries) {
        std::wcout << entry.url.c_str() << std::endl;
    }
}

void CardController::AddNewCard(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::LinksUpsert(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::EditCard(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

void CardController::RemoveCard(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {

        CardModelManager::CardModelManager manager;
        // TODO: Call DB Function
        auto resp = nlohmann::json::parse(manager.Create(requestArgs.dump()));

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessPost(message, processLogic);
}

//void CardController::DoAnswer(web::http::http_request message) {
//    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {
//
//        CardModelManager::CardModelManager manager;
//        auto resp = nlohmann::json::parse(manager.GetNextCard(requestArgs.dump()));
//
//        web::http::status_code status = ValidateManagerResponse(resp);
//
//        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
//    };
//
//    ProcessGet(message, processLogic);
//}

void CardController::GetCard(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {
        CardModelManager::CardModelManager manager;
        auto items = nlohmann::json::parse(manager.Get(requestArgs.dump()));

        auto resp_items = nlohmann::json::array();
        if (!items["links"].empty()) {
            for (auto &link : items["links"]) {
                resp_items.push_back(link);
            }
        }

        auto resp = items;
        resp["links"] = resp_items;

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void CardController::List(web::http::http_request message) {
    RequestLogicProcessor processLogic = [this](const nlohmann::json& requestArgs) {
        CardModelManager::CardModelManager manager;
        auto items = nlohmann::json::parse(manager.Get(requestArgs.dump()));
        // TODO: List from DB
        auto resp_items = nlohmann::json::array();
        if (!items["links"].empty()) {
            for (auto &link : items["links"]) {
                resp_items.push_back(link);
            }
        }

        auto resp = items;
        resp["links"] = resp_items;

        web::http::status_code status = ValidateManagerResponse(resp);

        return std::make_pair(status, converters::ConvertNlohmannToWebJSON(resp));
    };

    ProcessGet(message, processLogic);
}

void CardController::Get(web::http::http_request message) {

  RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {
    CardModelManager::CardModelManager manager;
    auto resp = nlohmann::json::parse(manager.Get(request_args.dump()));

    if (resp.find("links") != resp.end()) {
      nlohmann::json unpacked_links;
      for (const auto &link : resp["links"].get<std::map<std::string, std::string>>()) {
        unpacked_links.push_back(link.first);
      }
      resp["links"] = unpacked_links;
    }

    auto status = ValidateManagerResponse(resp);
    message.reply(status, converters::ConvertNlohmannToWebJSON(resp));
  };

  auto required_args_decorator
    = decorators::RequiredArgsDecorator({ "id" }, message, process_logic);

  ProcessGet(message, required_args_decorator);
}

void CardController::DoAnswer(web::http::http_request message) {
  RequestLogicProcessor process_logic = [this, message](nlohmann::json& request_args) {
    request_args["userId"] = request_args[USER_ID];
    request_args.erase(USER_ID);
    CardModelManager::CardModelManager manager;
    auto resp = nlohmann::json::parse(manager.GetNextCard(request_args.dump()));

    auto status = ValidateManagerResponse(resp);
    message.reply(status, converters::ConvertNlohmannToWebJSON(resp));
  };

  auto required_args_decorator
      = decorators::RequiredArgsDecorator({ "id", "answer" }, message, process_logic);

  auto login_required_decorator
    = decorators::LoginRequiredDecorator(message, process_logic);

  ProcessPost(message, login_required_decorator);
}

void CardController::ConfigureRouting() {
    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("do_answer"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, DoAnswer)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("remove"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, RemoveCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("edit"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, EditCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("links_upsert"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, LinksUpsert)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("add"),
            web::http::methods::POST,
            ASSIGN_HANDLER(CardController, AddNewCard)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("get"),
            web::http::methods::GET,
            ASSIGN_HANDLER(CardController, Get)
    });

    _routingEntries.push_back(networkhelper::RoutingEntry{
            U("list"),
            web::http::methods::GET,
            ASSIGN_HANDLER(CardController, List)
    });
}
