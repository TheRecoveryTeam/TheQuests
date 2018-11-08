#include <memory>

//
// Created by dpudov on 08.11.18.
//

#include "TheQuestsServer.h"
//#include "stdafx.h"

std::unique_ptr<TheQuestsServer> g_httpServer;

void on_initialize(const string_t &address) {
    uri_builder uri(address);
//    uri.append_path(U(""));

    auto addr = uri.to_uri().to_string();
    g_httpServer = std::make_unique<TheQuestsServer>(addr);
    g_httpServer->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
}

void on_shutdown() {
    g_httpServer->close().wait();
}

//
// To start the server, run the below command with admin privileges:
// TheQuestsServer.exe <port>
// If port is not specified, will listen on 34568
//
#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else

int main(int argc, char *argv[])
#endif
{
    utility::string_t port = U("34568");
    if (argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}

TheQuestsServer::TheQuestsServer(utility::string_t url) : m_listener(url) {
    m_listener.support(methods::GET, std::bind(&TheQuestsServer::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&TheQuestsServer::handle_post, this, std::placeholders::_1));

}

void TheQuestsServer::handle_get(http_request message) {

}

void TheQuestsServer::handle_post(http_request message) {

}
