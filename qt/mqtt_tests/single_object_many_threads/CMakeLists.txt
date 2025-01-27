cmake_minimum_required(VERSION 3.20)
project(mqtt_single_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(JSON_BuildTests OFF)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(api COMPONENTS  api_impl api_mqtt)
find_package(Qt6 COMPONENTS Core REQUIRED)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(mqtt_single_client_setIntProperty "client_setIntProperty.cpp" "../helpers/aync_int_property_testdata.cpp" "../../latency_helper/latency_helper.cpp")
add_executable(mqtt_single_client_syncSetIntProperty "client_setSyncIntProperty.cpp" "../../latency_helper/latency_helper.cpp")
add_executable(mqtt_single_client_asyncIntMethod "client_asyncIntMethod.cpp" "../helpers/async_int_method_testdata.cpp" "../../latency_helper/latency_helper.cpp")
add_executable(mqtt_single_client_syncIntMethod "client_syncIntMethod.cpp" "../helpers/sync_int_method_testdata.cpp" "../../latency_helper/latency_helper.cpp")
add_executable(mqtt_single_client_setStringProperty "client_setStringProperty.cpp" "../../latency_helper/latency_helper.cpp")
add_executable(mqtt_single_server "server.cpp" )

target_link_libraries(mqtt_single_server  api::api_mqtt api::api_impl)
target_link_libraries(mqtt_single_client_setIntProperty api::api_mqtt Qt6::Core)
target_link_libraries(mqtt_single_client_asyncIntMethod api::api_mqtt Qt6::Core)
target_link_libraries(mqtt_single_client_syncIntMethod api::api_mqtt Qt6::Core)
target_link_libraries(mqtt_single_client_syncSetIntProperty api::api_mqtt Qt6::Core)
target_link_libraries(mqtt_single_client_setStringProperty api::api_mqtt)
