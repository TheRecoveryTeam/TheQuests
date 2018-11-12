#include <iostream>

#include "controllers/UserInterruptHandler.h"
#include "controllers/RuntimeUtils.h"

#include "controllers/card/CardController.h"
#include "controllers/user/UserController.h"
#include "controllers/quest/QuestController.h"

using namespace networkhelper;
using namespace web;

int main(int argc, char **argv) {
    InterruptHandler::hookSIGINT();

    CardController cardController;
    cardController.setEndpoint("localhost:8080/api/card");

//    UserController userController;
//    userController.setEndpoint("localhost:8080/api/user");

//    QuestController questController;
//    questController.setEndpoint("localhost:8080/api/quest");

    try {
        // wait for server initialization...
        cardController.accept().wait();
        std::cout << "CardController is listening: " << cardController.endpoint() << std::endl;

        // userController.accept().wait();
        // std::cout << "UserController is listening: " << userController.endpoint() << std::endl;

        // questController.accept().wait();
        // std::cout << "QuestController is listening: " << questController.endpoint() << std::endl;

        InterruptHandler::waitForUserInterrupt();

        cardController.shutdown().wait();
    }
    catch (std::exception &e) {
        std::cerr << "Internal server ERROR" << '\n';
    }
    catch (...) {
        RuntimeUtils::printStackTrace();
    }

    return 0;
}