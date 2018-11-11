cmake_minimum_required(VERSION 3.10)
project(models)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(nlohmann_json 3.4.0 REQUIRED)

#set (SOURCE_LIB ${PROJECT_SOURCE_DIR}/src/storage/models/*.cpp)
file(GLOB model_srcs ${PROJECT_SOURCE_DIR}/models/*.cpp)
message(STATUS "${model_srcs}")
add_library(models STATIC ${model_srcs})
message(STATUS "${model_srcs}")
#include_directories(${PROJECT_SOURCE_DIR}/../engine/)
#add_subdirectory(${PROJECT_SOURCE_DIR}/../engine/)
target_include_directories(models PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/models
        )
target_link_libraries(models
        ${LIBMONGOCXX_LIBRARIES}
        nlohmann_json::nlohmann_json
        )