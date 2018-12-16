cmake_minimum_required(VERSION 3.10)
project(src)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(nlohmann_json 3.4.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(Boost COMPONENTS thread chrono system REQUIRED)

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


file(GLOB converters_utils_srcs ${PROJECT_SOURCE_DIR}/utils/converters/*.cpp)
message(STATUS "${converters_utils_srcs}")
add_library(converters_utils STATIC ${converters_utils_srcs})
message(STATUS "${converters_utils_srcs}")
target_include_directories(converters_utils PUBLIC
        ${PROJECT_SOURCE_DIR}/model_manager
        )
target_link_libraries(converters_utils
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        Boost::thread
        )


file(GLOB controller_utils_srcs ${PROJECT_SOURCE_DIR}/utils/controller/*.cpp)
message(STATUS "${controller_utils_srcs}")
add_library(controller_utils STATIC ${controller_utils_srcs})
message(STATUS "${controller_utils_srcs}")
target_include_directories(controller_utils PUBLIC
        ${PROJECT_SOURCE_DIR}/controller
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(controller_utils
        cpprestsdk::cpprest
        ${Boost_LIBRARIES}
        Boost::system
        Boost::thread
        Boost::chrono
        )


file(GLOB abstract_decorator_utils_srcs ${PROJECT_SOURCE_DIR}/utils/decorators/abstract_decorator/*.cpp)
message(STATUS "${abstract_decorator_utils_srcs}")
add_library(abstract_decorator_utils STATIC ${abstract_decorator_utils_srcs})
message(STATUS "${abstract_decorator_utils_srcs}")
target_include_directories(abstract_decorator_utils PUBLIC
        ${PROJECT_SOURCE_DIR}/decorators/abstract_decorator
        )
target_link_libraries(abstract_decorator_utils
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        Boost::thread
        )


file(GLOB login_required_utils_srcs ${PROJECT_SOURCE_DIR}/utils/decorators/login_required/*.cpp)
message(STATUS "${login_required_utils_srcs}")
add_library(login_required_utils STATIC ${login_required_utils_srcs})
message(STATUS "${login_required_utils_srcs}")
target_include_directories(login_required_utils PUBLIC
        ${PROJECT_SOURCE_DIR}/decorators/login_required
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(login_required_utils
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        sessionmodel
        Boost::thread
        )


file(GLOB required_args_utils_srcs ${PROJECT_SOURCE_DIR}/utils/decorators/required_args/*.cpp)
message(STATUS "${required_args_utils_srcs}")
add_library(required_args_utils STATIC ${required_args_utils_srcs})
message(STATUS "${required_args_utils_srcs}")
target_include_directories(required_args_utils PUBLIC
        ${PROJECT_SOURCE_DIR}/decorators/required_args
        )
target_link_libraries(required_args_utils
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        Boost::thread
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
        OpenSSL::SSL
        sessionmodel
        )


file(GLOB controller_srcs ${PROJECT_SOURCE_DIR}/core/controller/*.cpp)
message(STATUS "${controller_srcs}")
add_library(abstractcontroller STATIC ${controller_srcs})
message(STATUS "${controller_srcs}")
target_include_directories(abstractcontroller PUBLIC
        ${PROJECT_SOURCE_DIR}/contoller
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(abstractcontroller PUBLIC
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        sessionmodel
        Boost::thread
        )


file(GLOB card_controller_srcs ${PROJECT_SOURCE_DIR}/card/controller/*.cpp)
message(STATUS "${card_controller_srcs}")
add_library(cardcontroller STATIC ${card_controller_srcs})
message(STATUS "${card_controller_srcs}")
target_include_directories(cardcontroller PUBLIC
        ${PROJECT_SOURCE_DIR}/contoller
        ${OPENSSL_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(cardcontroller PUBLIC
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        cardmodel
        OpenSSL::Crypto
        OpenSSL::SSL
        Boost::thread
        )


file(GLOB quest_controller_srcs ${PROJECT_SOURCE_DIR}/quest/controller/*.cpp)
message(STATUS "${quest_controller_srcs}")
add_library(questcontroller STATIC ${quest_controller_srcs})
message(STATUS "${quest_controller_srcs}")
target_include_directories(questcontroller PUBLIC
        ${PROJECT_SOURCE_DIR}/contoller
        ${OPENSSL_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(questcontroller PUBLIC
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        questmodel
        OpenSSL::Crypto
        OpenSSL::SSL
        Boost::thread
        )


file(GLOB user_controller_srcs ${PROJECT_SOURCE_DIR}/user/controller/*.cpp)
message(STATUS "${user_controller_srcs}")
add_library(usercontroller STATIC ${user_controller_srcs})
message(STATUS "${user_controller_srcs}")
target_include_directories(usercontroller PUBLIC
        ${PROJECT_SOURCE_DIR}/contoller
        ${OPENSSL_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(usercontroller PUBLIC
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        usermodel
        OpenSSL::Crypto
        OpenSSL::SSL
        Boost::thread
        )


add_library(microservice INTERFACE)
target_sources(microservice INTERFACE ${PROJECT_SOURCE_DIR}/utils/controller/MicroService.h)

target_include_directories(microservice INTERFACE
        ${PROJECT_SOURCE_DIR}/controller
        ${BOOST_INCLUDE_DIR}
        )
target_link_libraries(microservice INTERFACE
        ${Boost_LIBRARIES}
        Boost::thread
        Boost::system
        Boost::chrono
        )