cmake_minimum_required(VERSION 3.10)
project(connections)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)


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