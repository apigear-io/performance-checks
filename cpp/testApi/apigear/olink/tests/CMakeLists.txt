cmake_minimum_required(VERSION 3.20)
project(test_poco_olink)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

if(BUILD_TESTING)
enable_testing()

Include(FetchContent)

find_package(Catch2 QUIET)
find_package(trompeloeil QUIET)

Include(FetchContent)
if (NOT Catch2_Found)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.8
    GIT_SHALLOW    TRUE
    FIND_PACKAGE_ARGS)
FetchContent_MakeAvailable(Catch2)
endif()

if(NOT trompeloeil_Found)
FetchContent_Declare(
    trompeloeil
    GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
    GIT_TAG        8480eda8bcda5ac85ef18866047f485d7d2392f5
    )
FetchContent_MakeAvailable(trompeloeil)
endif()


set(TEST_POCO_OLINK_SOURCES
    test_main.cpp
    olink_connection.test.cpp
    olinkhost.test.cpp
    olinklogadapter.test.cpp
    test_main.cpp
    private/frame.hpp
    private/sinkobjectmock.hpp
    private/test_server/test_server.hpp
    private/test_server/test_server_request_factory.hpp
    private/test_server/iframestorage.hpp
    private/test_server/test_server_request_handler.hpp
    )

add_executable(test_poco_olink ${TEST_POCO_OLINK_SOURCES})


add_test(NAME test_poco_olink COMMAND $<TARGET_FILE:test_poco_olink>)

target_link_libraries(test_poco_olink PRIVATE poco-olink Catch2::Catch2 trompeloeil::trompeloeil)

endif() # BUILD_TESTING
