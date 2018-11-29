cmake_minimum_required(VERSION 3.10)
project(connections)

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)

#set (SOURCE_LIB ${PROJECT_SOURCE_DIR}/src/storage/models/*.cpp)
file(GLOB connection_srcs ${PROJECT_SOURCE_DIR}/connections/*.cpp)
message(STATUS "${connection_srcs}")
add_library(connections STATIC ${connection_srcs})
message(STATUS "${connection_srcs}")
target_include_directories(connections PUBLIC
        ${LIBMONGOCXX_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/connections
        )
target_link_libraries(connections
        ${LIBMONGOCXX_LIBRARIES}
        )
