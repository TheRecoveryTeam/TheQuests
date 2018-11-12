//
// Created by Арсений Зорин on 11/11/2018.
//


#include <iostream>
#include "Connection_singleton.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>


MongoAccess::MongoAccess &MongoAccess::MongoAccess::instance() {
    static MongoAccess instance;
    return instance;
}

void MongoAccess::MongoAccess::configure(std::unique_ptr<mongocxx::instance> instance,
                                         std::unique_ptr<mongocxx::pool> pool) {
    _instance = std::move(instance);
    _pool = std::move(pool);
}

mongocxx::pool::entry MongoAccess::MongoAccess::get_connection() {
    return _pool->acquire();
}

