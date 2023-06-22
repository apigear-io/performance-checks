cmake_minimum_required(VERSION 3.1)
project(olink_mulitple_objects_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)

find_package(api COMPONENTS  api_impl api_olink)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slider )

find_package(Qt5 REQUIRED COMPONENTS Gui Quick QuickControls2 QuickWidgets)
add_executable(slider_server "slider/server/main.cpp" "slider/server/main.qml" "slider/server/resources.qrc")
add_executable(slider_client "slider/client/main.cpp" "slider/client/main.qml" "slider/client/resources.qrc")

target_link_libraries(slider_server api::api_olink  api::api_impl Qt5::Gui Qt5::Quick Qt5::QuickControls2 Qt5::QuickWidgets)
target_link_libraries(slider_client api::api_olink  api::api_impl Qt5::Gui Qt5::Quick Qt5::QuickControls2 Qt5::QuickWidgets)
