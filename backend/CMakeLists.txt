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
endif()

include(ExternalProject)

set(common_cmake_cache_args
        -DCMAKE_CXX_COMPILER:PATH=${CMAKE_CXX_COMPILER}
        )
if(NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    list(APPEND common_cmake_cache_args
            -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
            )
endif()

ExternalProject_Add(libmongoc
        GIT_REPOSITORY  "https://github.com/TheRecoveryTeam/mongo-c-driver.git"
        GIT_TAG         "1.12.0"
        GIT_PROGRESS    1
        GIT_SHALLOW     1
        SOURCE_DIR      "${THIRD_PARTY_DIR}/libmongoc"
        BINARY_DIR      "${THIRD_PARTY_DIR}/libmongoc-build"
        INSTALL_DIR     "${THIRD_PARTY_DIR}/libmongoc-install"
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
        GIT_REPOSITORY  "https://github.com/TheRecoveryTeam/mongo-c-driver.git"
#        GIT_TAG         "r3.4.0"
        GIT_PROGRESS    1
        GIT_SHALLOW     1
        SOURCE_DIR      "${THIRD_PARTY_DIR}/libmongocxx"
        BINARY_DIR      "${THIRD_PARTY_DIR}/libmongocxx-build"
        INSTALL_DIR     "${THIRD_PARTY_DIR}/libmongocxx-install"
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
        GIT_REPOSITORY  "https://github.com/TheRecoveryTeam/cpprestsdk.git"
        GIT_PROGRESS    1
        GIT_SHALLOW     1
        SOURCE_DIR      "${THIRD_PARTY_DIR}/cpprestsdk"
        BINARY_DIR      "${THIRD_PARTY_DIR}/cpprestsdk-build"
        INSTALL_DIR     "${THIRD_PARTY_DIR}/cpprestsdk-install"
        CMAKE_CACHE_ARGS
        ${common_cmake_cache_args}
        -DCMAKE_INSTALL_PREFIX:PATH=${THIRD_PARTY_DIR}/cpprestsdk-install
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DENABLE_TESTS:BOOL=OFF
        -DENABLE_EXAMPLES:BOOL=OFF
        )
set(cpprestsdk_DIR "${THIRD_PARTY_DIR}/cpprestsdk-install/lib/cpprestsdk")

# Все ниже закоментить и запустить make в папке cmake-build-debug.
# Когда все библиотеки скачаются, раскоментить.
# TODO: убрать этот костыль

find_package(libmongoc REQUIRED NAMES libmongoc libmongoc-1.0)
find_package(libmongocxx REQUIRED NAMES libmongocxx libmongocxx-1.0)
find_package(Boost REQUIRED)
find_package(Boost REQUIRED system)
find_package(cpprestsdk REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} cpprestsdk::cpprest ${Boost_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${LIBMONGOCXX_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${LIBMONGOCXX_DEFINITIONS})
