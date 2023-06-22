include(CTest)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  # pull nlohmann json as dependency
  message(STATUS "nlohmann_json NOT FOUND, fetching the release package")
  include(FetchContent)
  set(JSON_Install ON)
  FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
  FetchContent_MakeAvailable(json)
endif()


set (SOURCES
    tracer.cpp
)
add_library(poco-tracer SHARED ${SOURCES})
add_library(apigear::poco-tracer ALIAS poco-tracer)
target_include_directories(poco-tracer
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(poco-tracer PUBLIC Poco::Net Poco::Util apigear::utilities nlohmann_json::nlohmann_json)

# add test cases
if(BUILD_TESTING)
include(FetchContent)
if (NOT Catch2_Found)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.8
    GIT_SHALLOW    TRUE
    FIND_PACKAGE_ARGS)
FetchContent_MakeAvailable(Catch2)
endif()

set (SOURCES_TEST
    ../apigear.test.cpp
    tracer.test.cpp
)
add_executable(test_tracer
    ${SOURCES_TEST}
)
target_include_directories(test_tracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_tracer PRIVATE apigear::poco-tracer Catch2::Catch2)

add_test(NAME test_tracer COMMAND $<TARGET_FILE:test_tracer>)
endif(BUILD_TESTING)

# install binary files
install(TARGETS poco-tracer
        EXPORT ApiGearPocoTracerTargets
        RUNTIME DESTINATION bin           COMPONENT Runtime
        LIBRARY DESTINATION lib           COMPONENT Runtime
        ARCHIVE DESTINATION lib           COMPONENT Development)
# install includes
FILE(GLOB APIGEAR_INCLUDES *.h)
install(FILES ${APIGEAR_INCLUDES}
        DESTINATION include/apigear/tracer)

export(EXPORT ApiGearPocoTracerTargets
    NAMESPACE apigear::
)

install(EXPORT ApiGearPocoTracerTargets
    FILE ApiGearPocoTracerTargets.cmake
    DESTINATION ${InstallDir}
    NAMESPACE apigear::
)
