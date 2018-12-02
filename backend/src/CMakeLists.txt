cmake_minimum_required(VERSION 3.10)
project(src)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(nlohmann_json 3.4.0 REQUIRED)
find_package(OpenSSL REQUIRED)

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
        model_manager_utils
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

file(GLOB model_manager_srcs ${PROJECT_SOURCE_DIR}/core/model_manager/*.cpp)
message(STATUS "${model_manager_srcs}")
add_library(abstractmodel STATIC ${model_manager_srcs})
message(STATUS "${model_manager_srcs}")
target_include_directories(abstractmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/model_manager
        )
target_link_libraries(abstractmodel
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        model_manager_utils
        )

file(GLOB model_manager_utils_srcs ${PROJECT_SOURCE_DIR}/utils/model_manager/*.cpp)
message(STATUS "${model_manager_utils_srcs}")
add_library(model_manager_utils STATIC ${model_manager_utils_srcs})
message(STATUS "${model_manager_utils_srcs}")
target_include_directories(model_manager_utils PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/model_manager
        )
target_link_libraries(model_manager_utils
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        )


file(GLOB session_model_srcs ${PROJECT_SOURCE_DIR}/session/model_manager/*.cpp)
message(STATUS "${session_model_srcs}")
add_library(sessionmodel STATIC ${session_model_srcs})
target_include_directories(sessionmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/session/model_manager
        ${OPENSSL_INCLUDE_DIR}
        )
target_link_libraries(sessionmodel
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        model_manager_utils
        OpenSSL::Crypto
        )


file(GLOB user_model_srcs ${PROJECT_SOURCE_DIR}/user/model_manager/*.cpp)
message(STATUS "${user_model_srcs}")
add_library(usermodel STATIC ${user_model_srcs})
target_include_directories(sessionmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/user/model_manager
        ${OPENSSL_INCLUDE_DIR}
        )
target_link_libraries(usermodel
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        model_manager_utils
        OpenSSL::Crypto
        )