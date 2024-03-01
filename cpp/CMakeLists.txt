cmake_minimum_required(VERSION 3.1)
project(performace_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

option(MANY_OBJECT_TESTS "build test for api generated for many objects" OFF)

if(NOT TARGET check)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
endif()

add_subdirectory(testApi)
add_subdirectory(olink_tests/olink_core_only_tests)
add_subdirectory(olink_tests/single_object_many_threads)
add_subdirectory(mqtt_tests/single_object_many_threads)
if(MANY_OBJECT_TESTS)
add_subdirectory(olink_tests/many_objects)
add_subdirectory(mqtt_tests/many_objects)
endif()