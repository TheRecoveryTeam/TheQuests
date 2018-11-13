cmake_minimum_required(VERSION 3.10)
project(src)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(nlohmann_json 3.4.0 REQUIRED)

file(GLOB card_model_manager_srcs ${PROJECT_SOURCE_DIR}/card/model_manager/*.cpp)
message(STATUS "${card_model_manager_srcs}")
add_library(cardmodelmanager STATIC ${card_model_manager_srcs})
target_include_directories(cardmodelmanager PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/card/model_manager
        )
target_link_libraries(cardmodelmanager
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        )

file(GLOB database_connection_srcs ${PROJECT_SOURCE_DIR}/engine/connections/*.cpp)
message(STATUS "${database_connection_srcs}")
add_library(databaseconnection STATIC ${database_connection_srcs})
message(STATUS "${database_connection_srcs}")
target_include_directories(databaseconnection PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/engine/connections
        )
target_link_libraries(databaseconnection
        ${LIBMONGOCXX_LIBRARIES}
        )