cmake_minimum_required(VERSION 3.10)
project(core)
#set(CMAKE_PREFIX_PATH ../../cmake-build-debug/thirdparty)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(cpprestsdk REQUIRED NAMES cpprestsdk)


file(GLOB model_manager_srcs ${PROJECT_SOURCE_DIR}/model_manager/*.cpp)
message(STATUS "${model_manager_srcs}")
add_library(abstractmodel STATIC ${model_manager_srcs})
message(STATUS "${model_manager_srcs}")
target_include_directories(abstractmodel PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/model_manager
        )
target_link_libraries(abstractmodel
        ${LIBMONGOCXX_LIBRARIES}
        )


file(GLOB controller_srcs ${PROJECT_SOURCE_DIR}/controller/*.cpp)
message(STATUS "${controller_srcs}")
add_library(abstractcontroller STATIC ${controller_srcs})
message(STATUS "${controller_srcs}")
target_include_directories(abstractcontroller PUBLIC
        ${PROJECT_SOURCE_DIR}/contoller
        )
target_link_libraries(abstractcontroller PUBLIC
        cpprestsdk::cpprest
        nlohmann_json::nlohmann_json
        )