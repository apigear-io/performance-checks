cmake_minimum_required(VERSION 3.1)
project(olink_mulitple_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS api-olink  api-implementation)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

add_executable(olink_mulit_client_setIntProperty "client_setIntProperty.cpp" )
add_executable(olink_mulit_client_setFloatProperty "client_setFloatProperty.cpp" )
add_executable(olink_mulit_client_setStringProperty "client_setStringProperty.cpp" )
add_executable(olink_mulit_server "server.cpp" "../helpers/prepare_test_services.cpp" )

target_link_libraries(olink_mulit_client_setIntProperty api::api-olink)
target_link_libraries(olink_mulit_client_setFloatProperty api::api-olink)
target_link_libraries(olink_mulit_client_setStringProperty api::api-olink)
target_link_libraries(olink_mulit_server api::api-olink  api::api-implementation)

