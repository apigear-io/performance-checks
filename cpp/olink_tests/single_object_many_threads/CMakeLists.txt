cmake_minimum_required(VERSION 3.1)
project(olink_single_object_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS api-olink  api-implementation)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(olink_single_client_syncSetIntProperty "client_syncSetIntProperty.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_single_client_setIntProperty "client_setIntProperty.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_single_client_setStringProperty "client_setStringProperty.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_single_client_syncMethodInt "client_syncIntMethodCall.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_single_client_asyncMethodInt "client_asyncIntMethodCall.cpp" "../helpers/latency_helpers.cpp")
add_executable(olink_single_server "server.cpp" )

target_link_libraries(olink_single_client_setIntProperty api::api-olink)
target_link_libraries(olink_single_client_syncSetIntProperty api::api-olink)
target_link_libraries(olink_single_client_syncMethodInt api::api-olink)
target_link_libraries(olink_single_client_asyncMethodInt api::api-olink)
target_link_libraries(olink_single_client_setStringProperty api::api-olink)
target_link_libraries(olink_single_server api::api-olink  api::api-implementation)

