cmake_minimum_required(VERSION 3.12)
if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()

project(TheQuests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE debug)
set(THIRD_PARTY_DIR ${CMAKE_BINARY_DIR}/thirdparty)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost COMPONENTS system REQUIRED)
if (Boost_FOUND)
    set(Boost_USE_STATIC_LIBS TRUE)
endif ()
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
endif ()

if (UNIX)
    set(CppRest_ROOT "${CMAKE_SOURCE_DIR}/lib/cpprestsdk")
    set(CppRest_INCLUDE_DIR "${CppRest_ROOT}/Release/include")
    set(CppRest_LIBRARY "${CppRest_ROOT}/build.release/Binaries/libcpprest.a")
elseif (WIN32)
    find_package(CppRestSDK REQUIRED)
    set(CppRest_LIBRARY cpprestsdk::cpprest)
else ()
    find_package(CppRest REQUIRED)
endif ()

message("Found CppRest ${CppRest_INCLUDE_DIR} ${CppRest_LIBRARY}")
include_directories(cpprestsdk_INCLUDE_DIRS)

option(${PROJECT_NAME}_SUPERBUILD "Build ${PROJECT_NAME} and the projects it depends on." ON)

if (${PROJECT_NAME}_SUPERBUILD)
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
            GIT_REPOSITORY "https://github.com/mongodb/mongo-cxx-driver.git"
            GIT_TAG "r3.3.1"
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
    set(libmongocxx_DIR "${THIRD_PARTY_DIR}/libmongocxx-install/lib/cmake/libmongocxx-3.3.1/")
    set(libbsoncxx_DIR "${THIRD_PARTY_DIR}/libmongocxx-install//lib/cmake/libbsoncxx-3.3.1/")
    function(ExternalProject_AlwaysConfigure proj)
        _ep_get_step_stampfile(${proj} "configure" stampfile)
        ExternalProject_Add_Step(${proj} forceconfigure
                COMMAND ${CMAKE_COMMAND} -E remove ${stampfile}
                COMMENT "Forcing configure step for '${proj}'"
                DEPENDEES build
                ALWAYS 1
                )
    endfunction()

    ExternalProject_Add(${PROJECT_NAME}
            SOURCE_DIR "${CMAKE_SOURCE_DIR}"
            BINARY_DIR "${THIRD_PARTY_DIR}/${PROJECT_NAME}-build"
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
            CMAKE_CACHE_ARGS
            ${common_cmake_cache_args}
            -D${PROJECT_NAME}_SUPERBUILD:BOOL=OFF
            -Dlibbsoncxx_DIR:PATH=${libbsoncxx_DIR}
            -Dlibmongocxx_DIR:PATH=${libmongocxx_DIR}
            INSTALL_COMMAND ""
            DEPENDS
            libmongocxx
            )
    ExternalProject_AlwaysConfigure(${PROJECT_NAME})
endif ()

find_package(libmongocxx REQUIRED)
message("Found libmongocxx ${LIBMONGOCXX_LIBRARIES}")
message("Found libbsoncxx ${LIBBSONCXX_LIBRARIES}")
set(LIB_NO_ABI "${THIRD_PARTY_DIR}/libmongocxx-install/lib/libbsoncxx.so._noabi")

link_directories(
        ${LIBMONGOCXX_LIBRARY_DIRS}
        ${LIBBSONCXX_LIBRARY_DIRS}
)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories(${INCLUDE_DIR})
link_directories(${INCLUDE_DIR})

configure_file(CMakeLists.txt.in ${THIRD_PARTY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${THIRD_PARTY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${THIRD_PARTY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${THIRD_PARTY_DIR}/googletest-src
        ${THIRD_PARTY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_executable(test
        TheQuestsServer.cpp
        controllers/AbstractController.h
        controllers/card/CardController.cpp
        controllers/card/CardController.h
        controllers/RequestRouter.cpp
        controllers/RequestRouter.h
        controllers/NetworkHelper.h
        controllers/AbstractController.cpp
        controllers/NetworkUtils.h
        controllers/MicroService.h
        controllers/NetworkUtils.cpp
        controllers/RuntimeUtils.h
        controllers/UserInterruptHandler.h
        controllers/Handler.h
        controllers/quest/QuestController.cpp
        controllers/quest/QuestController.h controllers/user/UserController.cpp controllers/user/UserController.h)

add_custom_target(run
        COMMAND test
        DEPENDS test
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        )

target_link_libraries(test LINK_PUBLIC cpprest ${Boost_LIBRARIES} OpenSSL::Crypto ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})
target_include_directories(test PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_compile_definitions(test PUBLIC ${LIBMONGOCXX_DEFINITIONS})


list(FIND LIBMONGOCXX_DEFINITIONS "BSONCXX_STATIC" LIST_IDX)
if (${LIST_IDX} GREATER -1)
    message(FATAL_ERROR "Expected BSONCXX_STATIC to not be defined")
endif ()

list(FIND LIBMONGOCXX_DEFINITIONS "MONGOCXX_STATIC" LIST_IDX)
if (${LIST_IDX} GREATER -1)
    message(FATAL_ERROR "Expected MONGOCXX_STATIC to not be defined")
endif ()
