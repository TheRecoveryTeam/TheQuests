#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


int main(int, char **) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27017"}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["user"];
    document << "hello" << "world";
    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto &&doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    return 0;
}