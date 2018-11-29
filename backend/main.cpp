#include <iostream>

#include "src/controllers/card/CardController.h"
#include "src/controllers/user/UserController.h"
#include "src/controllers/quest/QuestController.h"
#include "src/controllers/UserInterruptHandler.h"
#include "src/controllers/RuntimeUtils.h"

using namespace networkhelper;
using namespace web;

int main(int argc, char **argv) {
    InterruptHandler::hookSIGINT();

    CardController cardController;
    cardController.setEndpoint("http://host_auto_ip4:8800/api/card/");

    UserController userController;
    userController.setEndpoint("http://host_auto_ip4:8800/api/user/");

    QuestController questController;
    questController.setEndpoint("http://host_auto_ip4:8800/api/quest/");

    try {
        // wait for server initialization...
        cardController.accept().wait();
        std::wcout << U("CardController is listening: ") << std::endl;
        cardController.endpoint();

        userController.accept().wait();
        std::wcout << "UserController is listening: " << std::endl;
        userController.endpoint();

        questController.accept().wait();
        std::wcout << "QuestController is listening: " << std::endl;
        questController.endpoint();

        InterruptHandler::waitForUserInterrupt();

        cardController.shutdown().wait();
        userController.shutdown().wait();
        questController.shutdown().wait();
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