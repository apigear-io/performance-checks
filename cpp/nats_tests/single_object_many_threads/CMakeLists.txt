cmake_minimum_required(VERSION 3.20)
project(nats_single_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(JSON_BuildTests OFF)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(api COMPONENTS  api-implementation api-nats)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(nats_single_client_setIntProperty "client_setIntProperty.cpp" "../helpers/latency_helpers.cpp")
#add_executable(nats_single_client_setStringProperty "client_setStringProperty.cpp" )
add_executable(nats_single_server "server.cpp" )
add_executable(nats_single_client_syncSetIntProperty "client_syncSetIntProperty.cpp" "../helpers/latency_helpers.cpp")
add_executable(nats_single_client_syncMethodInt "client_syncIntMethodCall.cpp" "../helpers/latency_helpers.cpp")
add_executable(nats_single_client_asyncMethodInt "client_asyncIntMethodCall.cpp" "../helpers/latency_helpers.cpp")

target_link_libraries(nats_single_server  api::api-nats api::api-implementation)
target_link_libraries(nats_single_client_setIntProperty api::api-nats)
target_link_libraries(nats_single_client_syncSetIntProperty api::api-nats)
target_link_libraries(nats_single_client_syncMethodInt api::api-nats)
target_link_libraries(nats_single_client_asyncMethodInt api::api-nats)
#target_link_libraries(nats_single_client_setStringProperty api::api-nats)
