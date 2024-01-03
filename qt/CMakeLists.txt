cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(performace_tests LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(JSON_BuildTests OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)


include(FetchContent)

FetchContent_Declare(qtpromise
  GIT_REPOSITORY https://github.com/simonbrunel/qtpromise.git
  GIT_TAG v0.7.0
  GIT_SHALLOW true
)

# CMake v3.14+
FetchContent_MakeAvailable(qtpromise)


add_subdirectory(testApi)
include_directories(testApi/thirdparty)
add_subdirectory(olink_tests/many_objects)
add_subdirectory(olink_tests/single_object_many_threads)
add_subdirectory(mqtt_tests/single_object_many_threads)
add_subdirectory(mqtt_tests/many_objects)

