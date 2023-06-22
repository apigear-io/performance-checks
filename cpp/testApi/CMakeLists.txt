cmake_minimum_required(VERSION 3.1)
project(test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# on Windows it is helpful to have all binary files next to each other
# it is intentionally not set as part of BUILD_TESTING to have a consistent behavior
# this can be removed once there is a better option than modifying the PATH env for unit testing
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_TESTING "Enable this option to build the test targets" OFF)

# enable testing
if(BUILD_TESTING)
include(CTest)
enable_testing()
endif(BUILD_TESTING)

    include(FetchContent)
# checks are workaround until generator support feature check properly
find_package(apigear QUIET)
if(NOT apigear_FOUND)
  # pull apigear as dependency
  message(STATUS "apigear NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(apigear
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/apigear"
  )
  FetchContent_MakeAvailable(apigear)
endif()
find_package(poco QUIET)
if(NOT poco_FOUND)

    # "poco:shared": False,
    set(ENABLE_DATA_MYSQL OFF CACHE BOOL "" FORCE)
    # "openssl:shared": False,
    set(ENABLE_ACTIVERECORD OFF CACHE BOOL "" FORCE)
    set(ENABLE_ACTIVERECORD_COMPILER OFF CACHE BOOL "" FORCE)
    set(ENABLE_APACHECONNECTOR OFF CACHE BOOL "" FORCE)
    set(ENABLE_CPPPARSER OFF CACHE BOOL "" FORCE)
    set(ENABLE_CRYPTO OFF CACHE BOOL "" FORCE)
    set(ENABLE_DATA OFF CACHE BOOL "" FORCE)
    set(ENABLE_DATA_ODBC OFF CACHE BOOL "" FORCE)
    set(ENABLE_DATA_POSTGRESQL OFF CACHE BOOL "" FORCE)
    set(ENABLE_DATA_SQLITE OFF CACHE BOOL "" FORCE)
    set(ENABLE_ENCODINGS OFF CACHE BOOL "" FORCE)
    set(ENABLE_JSON OFF CACHE BOOL "" FORCE)
    set(ENABLE_JWT OFF CACHE BOOL "" FORCE)
    set(ENABLE_MONGODB OFF CACHE BOOL "" FORCE)
    set(ENABLE_NET ON CACHE BOOL "" FORCE)
    set(ENABLE_NETSSL OFF CACHE BOOL "" FORCE)
    set(ENABLE_PAGECOMPILER  OFF CACHE BOOL "" FORCE)
    set(ENABLE_PAGECOMPILER_FILE2PAGE  OFF CACHE BOOL "" FORCE)
    set(ENABLE_PDF OFF CACHE BOOL "" FORCE)
    set(ENABLE_POCODOC OFF CACHE BOOL "" FORCE)
    set(ENABLE_REDIS OFF CACHE BOOL "" FORCE)
    set(ENABLE_SEVENZIP OFF CACHE BOOL "" FORCE)
    set(ENABLE_UTIL ON CACHE BOOL "" FORCE)
    set(ENABLE_XML OFF CACHE BOOL "" FORCE)
    set(ENABLE_ZIP OFF CACHE BOOL "" FORCE)
    include(FetchContent)
    FetchContent_Declare(
        Poco
        GIT_REPOSITORY https://github.com/pocoproject/poco.git
        GIT_TAG poco-1.11.6-release
        )
    FetchContent_MakeAvailable(Poco)
endif()
find_package(api QUIET)
if(NOT api_FOUND)
  # pull api as dependency
  message(STATUS "api NOT FOUND, building from source folder")
  include(FetchContent)
  FetchContent_Declare(api
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/modules/api_module/api"
  )
  FetchContent_MakeAvailable(api)
endif()
