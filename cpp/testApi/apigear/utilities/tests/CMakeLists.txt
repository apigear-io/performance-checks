cmake_minimum_required(VERSION 3.20)
project(test_apigear_utilities)

set(SPDLOG_DEBUG_ON true)
set(SPDLOG_TRACE_ON true)
include(CTest)

if(BUILD_TESTING)
enable_testing()

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.8
    GIT_SHALLOW    TRUE
    FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(Catch2)

set(TEST_APIGEAR_UTILITIES_SOURCES
    test_main.cpp
    logger.test.cpp
    )

add_executable(test_apigear_utilities ${TEST_APIGEAR_UTILITIES_SOURCES})


add_test(NAME test_apigear_utilities COMMAND $<TARGET_FILE:test_apigear_utilities>)

target_link_libraries(test_apigear_utilities PRIVATE apigear::utilities Catch2::Catch2)

endif() # BUILD_TESTING
