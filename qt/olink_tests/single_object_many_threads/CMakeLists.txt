cmake_minimum_required(VERSION 3.1)
project(olink_mulitple_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS  api_impl api_olink)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )


add_executable(olink_single_client_setIntProperty "client_setIntProperty.cpp")
add_executable(olink_single_client_setStringProperty "client_setStringProperty.cpp" )
add_executable(olink_single_server "server.cpp" )

target_link_libraries(olink_single_server api_olink api::api_impl)
target_link_libraries(olink_single_client_setIntProperty api_olink)
target_link_libraries(olink_single_client_setStringProperty api_olink)
