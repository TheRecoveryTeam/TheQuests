cmake_minimum_required(VERSION 3.10)
project(src)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(nlohmann_json 3.4.0 REQUIRED)

file(GLOB card_model_srcs ${PROJECT_SOURCE_DIR}/card/model_manager/*.cpp)
message(STATUS "${card_model_srcs}")
add_library(cardmodel STATIC ${card_model_srcs})
target_include_directories(cardmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/card/model_manager
        )
target_link_libraries(cardmodel
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        )

file(GLOB quest_model_srcs ${PROJECT_SOURCE_DIR}/quest/model_manager/*.cpp)
message(STATUS "${quest_model_srcs}")
add_library(questmodel STATIC ${quest_model_srcs})
target_include_directories(questmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/quest/model_manager
        )
target_link_libraries(questmodel
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        )

file(GLOB history_model_srcs ${PROJECT_SOURCE_DIR}/history/model_manager/*.cpp)
message(STATUS "${history_model_srcs}")
add_library(historymodel STATIC ${history_model_srcs})
target_include_directories(historymodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/history/model_manager
        )
target_link_libraries(historymodel
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