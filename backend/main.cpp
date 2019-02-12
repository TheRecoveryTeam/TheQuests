#include <iostream>

#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <engine/connections/DatabaseConnectionSingleton.h>
#include <nlohmann/json.hpp>

#include <card/controller/CardController.h>
#include <user/controller/UserController.h>
#include <quest/controller/QuestController.h>
#include <utils/controller/UserInterruptHandler.h>
#include <utils/controller/RuntimeUtils.h>


using namespace networkhelper;
using namespace web;

int main(int argc, char **argv) {
    InterruptHandler::hookSIGINT();

    CardController cardController;
    cardController.SetEndpoint("http://host_auto_ip4:8800/api/card/");

    UserController userController;
    userController.SetEndpoint("http://host_auto_ip4:8800/api/user/");

    QuestController questController;
    questController.SetEndpoint("http://host_auto_ip4:8800/api/quest/");

    auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
    auto uri = mongocxx::uri{"mongodb://localhost:27018"};
    MongoAccess::MongoAccess::instance().configure(std::move(instance),
                                                   bsoncxx::stdx::make_unique<mongocxx::pool>(std::move(uri)));

    try {
        // wait for server initialization...
        cardController.Accept().wait();
        std::wcout << U("CardController is listening: ") << std::endl;
        cardController.Endpoint();

        userController.Accept().wait();
        std::wcout << "UserController is listening: " << std::endl;
        userController.Endpoint();

        questController.Accept().wait();
        std::wcout << "QuestController is listening: " << std::endl;
        questController.Endpoint();

        InterruptHandler::waitForUserInterrupt();

        cardController.Shutdown().wait();
        userController.Shutdown().wait();
        questController.Shutdown().wait();
    }
    catch (std::exception &e) {
        std::wcout << U("Internal server ERROR") << std::endl;
        std::wcout << e.what() << std::endl;
    }
    catch (...) {
        RuntimeUtils::printStackTrace();
    }

    return 0;
}