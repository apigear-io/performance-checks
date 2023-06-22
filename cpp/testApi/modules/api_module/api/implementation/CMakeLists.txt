set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set (SOURCES_CORE_IMPL
    testapi0.cpp
    testapi1.cpp
    testapi2.cpp
    testapi3.cpp
    testapi4.cpp
    testapi5.cpp
    testapi6.cpp
    testapi7.cpp
    testapi8.cpp
    testapi9.cpp
    testapi10.cpp
    testapi11.cpp
    testapi12.cpp
    testapi13.cpp
    testapi14.cpp
    testapi15.cpp
    testapi16.cpp
    testapi17.cpp
    testapi18.cpp
    testapi19.cpp
    testapi20.cpp
    testapi21.cpp
    testapi22.cpp
    testapi23.cpp
    testapi24.cpp
    testapi25.cpp
    testapi26.cpp
    testapi27.cpp
    testapi28.cpp
    testapi29.cpp
    testapi30.cpp
    testapi31.cpp
    testapi32.cpp
    testapi33.cpp
    testapi34.cpp
    testapi35.cpp
    testapi36.cpp
    testapi37.cpp
    testapi38.cpp
    testapi39.cpp
    testapi40.cpp
    testapi41.cpp
    testapi42.cpp
    testapi43.cpp
    testapi44.cpp
    testapi45.cpp
    testapi46.cpp
    testapi47.cpp
    testapi48.cpp
    testapi49.cpp
    testapi50.cpp
    testapi51.cpp
    testapi52.cpp
    testapi53.cpp
    testapi54.cpp
    testapi55.cpp
    testapi56.cpp
    testapi57.cpp
    testapi58.cpp
    testapi59.cpp
    testapi60.cpp
    testapi61.cpp
    testapi62.cpp
    testapi63.cpp
    testapi64.cpp
    testapi65.cpp
    testapi66.cpp
    testapi67.cpp
    testapi68.cpp
    testapi69.cpp
    testapi70.cpp
    testapi71.cpp
    testapi72.cpp
    testapi73.cpp
    testapi74.cpp
    testapi75.cpp
    testapi76.cpp
    testapi77.cpp
    testapi78.cpp
    testapi79.cpp
    testapi80.cpp
    testapi81.cpp
    testapi82.cpp
    testapi83.cpp
    testapi84.cpp
    testapi85.cpp
    testapi86.cpp
    testapi87.cpp
    testapi88.cpp
    testapi89.cpp
    testapi90.cpp
    testapi91.cpp
    testapi92.cpp
    testapi93.cpp
    testapi94.cpp
    testapi95.cpp
    testapi96.cpp
    testapi97.cpp
    testapi98.cpp
    testapi99.cpp
)
add_library(api-implementation SHARED ${SOURCES_CORE_IMPL})
add_library(api::api-implementation ALIAS api-implementation)
target_include_directories(api-implementation
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../modules>
    $<INSTALL_INTERFACE:include/api>
)
target_link_libraries(api-implementation PUBLIC api::api-api api::api-core Threads::Threads)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(api-implementation PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(api-implementation PRIVATE /W4 /WX /wd4251)
endif()

# add test cases
if(BUILD_TESTING)
if (NOT Catch2_Found)
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.8
    GIT_SHALLOW    TRUE
    FIND_PACKAGE_ARGS)
FetchContent_MakeAvailable(Catch2)
endif()

set (SOURCES_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../generated/core/api.test.cpp
    testapi0.test.cpp
    testapi1.test.cpp
    testapi2.test.cpp
    testapi3.test.cpp
    testapi4.test.cpp
    testapi5.test.cpp
    testapi6.test.cpp
    testapi7.test.cpp
    testapi8.test.cpp
    testapi9.test.cpp
    testapi10.test.cpp
    testapi11.test.cpp
    testapi12.test.cpp
    testapi13.test.cpp
    testapi14.test.cpp
    testapi15.test.cpp
    testapi16.test.cpp
    testapi17.test.cpp
    testapi18.test.cpp
    testapi19.test.cpp
    testapi20.test.cpp
    testapi21.test.cpp
    testapi22.test.cpp
    testapi23.test.cpp
    testapi24.test.cpp
    testapi25.test.cpp
    testapi26.test.cpp
    testapi27.test.cpp
    testapi28.test.cpp
    testapi29.test.cpp
    testapi30.test.cpp
    testapi31.test.cpp
    testapi32.test.cpp
    testapi33.test.cpp
    testapi34.test.cpp
    testapi35.test.cpp
    testapi36.test.cpp
    testapi37.test.cpp
    testapi38.test.cpp
    testapi39.test.cpp
    testapi40.test.cpp
    testapi41.test.cpp
    testapi42.test.cpp
    testapi43.test.cpp
    testapi44.test.cpp
    testapi45.test.cpp
    testapi46.test.cpp
    testapi47.test.cpp
    testapi48.test.cpp
    testapi49.test.cpp
    testapi50.test.cpp
    testapi51.test.cpp
    testapi52.test.cpp
    testapi53.test.cpp
    testapi54.test.cpp
    testapi55.test.cpp
    testapi56.test.cpp
    testapi57.test.cpp
    testapi58.test.cpp
    testapi59.test.cpp
    testapi60.test.cpp
    testapi61.test.cpp
    testapi62.test.cpp
    testapi63.test.cpp
    testapi64.test.cpp
    testapi65.test.cpp
    testapi66.test.cpp
    testapi67.test.cpp
    testapi68.test.cpp
    testapi69.test.cpp
    testapi70.test.cpp
    testapi71.test.cpp
    testapi72.test.cpp
    testapi73.test.cpp
    testapi74.test.cpp
    testapi75.test.cpp
    testapi76.test.cpp
    testapi77.test.cpp
    testapi78.test.cpp
    testapi79.test.cpp
    testapi80.test.cpp
    testapi81.test.cpp
    testapi82.test.cpp
    testapi83.test.cpp
    testapi84.test.cpp
    testapi85.test.cpp
    testapi86.test.cpp
    testapi87.test.cpp
    testapi88.test.cpp
    testapi89.test.cpp
    testapi90.test.cpp
    testapi91.test.cpp
    testapi92.test.cpp
    testapi93.test.cpp
    testapi94.test.cpp
    testapi95.test.cpp
    testapi96.test.cpp
    testapi97.test.cpp
    testapi98.test.cpp
    testapi99.test.cpp
)
add_executable(test_api
    ${SOURCES_TEST}
)
target_link_libraries(test_api api::api-implementation Catch2::Catch2)
target_include_directories(test_api PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(test_api PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(test_api PRIVATE /W4 /WX /wd4251)
endif()

add_test(NAME test_api COMMAND $<TARGET_FILE:test_api>)
endif(BUILD_TESTING)

install(TARGETS api-implementation
        EXPORT ApiImplementationTargets
        RUNTIME DESTINATION bin                 COMPONENT Runtime
        LIBRARY DESTINATION lib                 COMPONENT Runtime
        ARCHIVE DESTINATION lib/api   COMPONENT Development)
# install includes
FILE(GLOB Api_INCLUDES *.h)
install(FILES ${Api_INCLUDES}
        DESTINATION include/api)

export(EXPORT ApiImplementationTargets
  NAMESPACE api::
)

install(EXPORT ApiImplementationTargets
  FILE ApiImplementationTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE api::
)
