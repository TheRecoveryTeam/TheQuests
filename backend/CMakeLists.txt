cmake_minimum_required(VERSION 3.10)
project(TheQuests)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        main.cpp
        )

set(SOURCE_FILES main.cpp)
set(THIRD_PARTY_DIR ${CMAKE_BINARY_DIR}/thirdparty)


if (APPLE)
    set(BOOST_ROOT /opt/local/include/boost/)
endif ()

include(ExternalProject)

set(common_cmake_cache_args
        -DCMAKE_CXX_COMPILER:PATH=${CMAKE_CXX_COMPILER}
        )
if (NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    list(APPEND common_cmake_cache_args
            -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
            )
endif ()

ExternalProject_Add(libmongoc
        GIT_REPOSITORY "https://github.com/TheRecoveryTeam/mongo-c-driver.git"
        GIT_TAG "1.12.0"
        GIT_PROGRESS 1
        GIT_SHALLOW 1
        SOURCE_DIR "${THIRD_PARTY_DIR}/libmongoc"
        BINARY_DIR "${THIRD_PARTY_DIR}/libmongoc-build"
        INSTALL_DIR "${THIRD_PARTY_DIR}/libmongoc-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/libmongoc-install
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_STATIC:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        -DENABLE_EXTRA_ALIGNMENT:BOOL=OFF
        )
set(libmongoc-1.0_DIR "${THIRD_PARTY_DIR}/libmongoc-install/lib/cmake/libmongoc-1.0/")
set(libbson-1.0_DIR "${THIRD_PARTY_DIR}/libmongoc-install/lib/cmake/libbson-1.0/")

ExternalProject_Add(libmongocxx
        GIT_REPOSITORY "https://github.com/TheRecoveryTeam/mongo-c-driver.git"
        #        GIT_TAG         "r3.4.0"
        GIT_PROGRESS 1
        GIT_SHALLOW 1
        SOURCE_DIR "${THIRD_PARTY_DIR}/libmongocxx"
        BINARY_DIR "${THIRD_PARTY_DIR}/libmongocxx-build"
        INSTALL_DIR "${THIRD_PARTY_DIR}/libmongocxx-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/libmongocxx-install
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        -DBSONCXX_POLY_USE_BOOST:BOOL=OFF
        -DBSONCXX_POLY_USE_MNMLSTC:BOOL=ON
        -DBSONCXX_POLY_USE_STD:BOOL=OFF
        -Dlibmongoc-1.0_DIR:PATH=${libmongoc-1.0_DIR}
        -Dlibbson-1.0_DIR:PATH=${libbson-1.0_DIR}
        DEPENDS
        libmongoc
        )
set(libmongocxx_DIR "${THIRD_PARTY_DIR}/libmongocxx-install/lib/cmake/libmongocxx-3.3.1")
set(libbsoncxx_DIR "${THIRD_PARTY_DIR}/libmongocxx-install/lib/cmake/libbsoncxx-3.3.1")
set(libmongoc_DIR ${libmongoc-1.0_DIR})

ExternalProject_Add(cpprestsdk
        GIT_REPOSITORY "https://github.com/TheRecoveryTeam/cpprestsdk.git"
        GIT_PROGRESS 1
        GIT_SHALLOW 1
        SOURCE_DIR "${THIRD_PARTY_DIR}/cpprestsdk"
        BINARY_DIR "${THIRD_PARTY_DIR}/cpprestsdk-build"
        INSTALL_DIR "${THIRD_PARTY_DIR}/cpprestsdk-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/cpprestsdk-install
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        )
set(cpprestsdk_DIR "${THIRD_PARTY_DIR}/cpprestsdk-install/lib/cpprestsdk")

ExternalProject_Add(googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "release-1.8.1"
        GIT_PROGRESS 1
        GIT_SHALLOW 1
        SOURCE_DIR "${THIRD_PARTY_DIR}/googletest"
        BINARY_DIR "${THIRD_PARTY_DIR}/googletest-build"
        INSTALL_DIR "${THIRD_PARTY_DIR}/googletest-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/googletest-install
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        )
set(GTest_DIR "${THIRD_PARTY_DIR}/googletest-install/lib/cmake/googletest")

ExternalProject_Add(nlohmann_json
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
        GIT_TAG "v3.4.0"
        GIT_PROGRESS 1
        GIT_SHALLOW 1
        SOURCE_DIR "${THIRD_PARTY_DIR}/nlohmann_json"
        BINARY_DIR "${THIRD_PARTY_DIR}/nlohmann_json-build"
        INSTALL_DIR "${THIRD_PARTY_DIR}/nlohmann_json-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/nlohmann_json-install
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        )
set(nlohmann_json_DIR "${THIRD_PARTY_DIR}/nlohmann_json-install/lib/cmake/nlohmann_json")


# Все ниже закоментить и запустить make в папке cmake-build-debug.
# Когда все библиотеки скачаются, раскоментить.
# TODO: убрать этот костыль

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(Boost REQUIRED)
find_package(Boost REQUIRED system)
find_package(cpprestsdk REQUIRED)
find_package(nlohmann_json 3.4.0 REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/src/)
add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json cpprestsdk::cpprest ${Boost_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${LIBMONGOCXX_LIBRARIES} cardmodel questmodel abstractmodel databaseconnection)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_DEFINITIONS})

add_executable(test tests/card/model_manager/CardModelManagerTests.cpp tests/quest/model_manager/QuestModelManagerTests.cpp
        tests/history/model_manager/HistoryModelManagerTests.cpp tests/card/model_manager/CardLinkModelManagerTests.cpp)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/thirdparty/googletest
        ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/googletest-build
        EXCLUDE_FROM_ALL)
target_link_libraries(test gtest_main nlohmann_json::nlohmann_json ${LIBMONGOCXX_LIBRARIES} cardmodel questmodel historymodel abstractmodel databaseconnection)
#target_link_libraries(test gtest_main nlohmann_json::nlohmann_json ${LIBMONGOCXX_LIBRARIES} questmodel historymodel abstractmodel databaseconnection cardmodel)
target_include_directories(test PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_compile_definitions(test PUBLIC ${LIBMONGOCXX_DEFINITIONS})
add_test(NAME CardModelManagerTest COMMAND test)
#add_test(NAME CardLinkModelManagerTest COMMAND test)
