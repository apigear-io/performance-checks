cmake_minimum_required(VERSION 3.1)
project(olink_mulitple_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS  api_impl api_olink)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/olink/many_objects )


add_executable(client_setIntProperty "client_setIntProperty.cpp" )
add_executable(client_setFloatProperty "client_setFloatProperty.cpp" )
add_executable(client_setStringProperty "client_setStringProperty.cpp" )
add_executable(server "server.cpp" "../helpers/prepare_test_services.cpp" )

target_link_libraries(client_setIntProperty api_olink)
target_link_libraries(client_setFloatProperty api_olink)
target_link_libraries(client_setStringProperty api_olink)
target_link_libraries(server api_olink  api::api_impl)
