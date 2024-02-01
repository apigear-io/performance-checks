cmake_minimum_required(VERSION 3.1)
project(olink_mulitple_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS api-olink  api-implementation)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

add_executable(olink_core_no_network_single_object_setIntProperty "olink_core_no_network_single_object_setIntProperty.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_core_no_network_single_object_syncIntMethodCall "olink_core_no_network_single_object_syncIntMethodCall.cpp" "../helpers/latency_helpers.cpp")


target_link_libraries(olink_core_no_network_single_object_setIntProperty api::api-olink  api::api-implementation)
target_link_libraries(olink_core_no_network_single_object_syncIntMethodCall api::api-olink  api::api-implementation)

