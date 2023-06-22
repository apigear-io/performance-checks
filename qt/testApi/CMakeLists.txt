cmake_minimum_required(VERSION 3.20)

project(qt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(JSON_BuildTests OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# on Windows it is helpful to have all binary files next to each other
# it is intentionally not set as part of BUILD_TESTING to have a consistent behavior
# this can be removed once there is a better option than modifying the PATH env for unit testing
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TESTING "Enable this option to build the test targets" OFF)

if(BUILD_TESTING)
find_package(Qt5 COMPONENTS Test REQUIRED)
enable_testing()
endif() # BUILD_TESTING

set(LIBRARY_PATH "${CMAKE_BINARY_DIR}/libs" CACHE STRING "Path where the libraries are deployed")
set(IMPORTS_PATH "${CMAKE_BINARY_DIR}/imports" CACHE STRING "Path where the plugins are deployed")

include_directories(thirdparty)
add_subdirectory(apigear)
add_subdirectory(thirdparty/qtpromise)
add_subdirectory(api/api)
add_subdirectory(api/implementation)
add_subdirectory(api/olink)
