set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
  # pull nlohmann json as dependency
  message(STATUS "nlohmann_json NOT FOUND, fetching the release package")
  include(FetchContent)
  set(JSON_Install ON)
  FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.7.3)
  FetchContent_MakeAvailable(json)
endif()

set (SOURCES_CORE_SUPPORT
    api.json.adapter.cpp
    testapi0.publisher.cpp
    testapi0.threadsafedecorator.cpp
    testapi1.publisher.cpp
    testapi1.threadsafedecorator.cpp
    testapi2.publisher.cpp
    testapi2.threadsafedecorator.cpp
    testapi3.publisher.cpp
    testapi3.threadsafedecorator.cpp
    testapi4.publisher.cpp
    testapi4.threadsafedecorator.cpp
    testapi5.publisher.cpp
    testapi5.threadsafedecorator.cpp
    testapi6.publisher.cpp
    testapi6.threadsafedecorator.cpp
    testapi7.publisher.cpp
    testapi7.threadsafedecorator.cpp
    testapi8.publisher.cpp
    testapi8.threadsafedecorator.cpp
    testapi9.publisher.cpp
    testapi9.threadsafedecorator.cpp
    testapi10.publisher.cpp
    testapi10.threadsafedecorator.cpp
    testapi11.publisher.cpp
    testapi11.threadsafedecorator.cpp
    testapi12.publisher.cpp
    testapi12.threadsafedecorator.cpp
    testapi13.publisher.cpp
    testapi13.threadsafedecorator.cpp
    testapi14.publisher.cpp
    testapi14.threadsafedecorator.cpp
    testapi15.publisher.cpp
    testapi15.threadsafedecorator.cpp
    testapi16.publisher.cpp
    testapi16.threadsafedecorator.cpp
    testapi17.publisher.cpp
    testapi17.threadsafedecorator.cpp
    testapi18.publisher.cpp
    testapi18.threadsafedecorator.cpp
    testapi19.publisher.cpp
    testapi19.threadsafedecorator.cpp
    testapi20.publisher.cpp
    testapi20.threadsafedecorator.cpp
    testapi21.publisher.cpp
    testapi21.threadsafedecorator.cpp
    testapi22.publisher.cpp
    testapi22.threadsafedecorator.cpp
    testapi23.publisher.cpp
    testapi23.threadsafedecorator.cpp
    testapi24.publisher.cpp
    testapi24.threadsafedecorator.cpp
    testapi25.publisher.cpp
    testapi25.threadsafedecorator.cpp
    testapi26.publisher.cpp
    testapi26.threadsafedecorator.cpp
    testapi27.publisher.cpp
    testapi27.threadsafedecorator.cpp
    testapi28.publisher.cpp
    testapi28.threadsafedecorator.cpp
    testapi29.publisher.cpp
    testapi29.threadsafedecorator.cpp
    testapi30.publisher.cpp
    testapi30.threadsafedecorator.cpp
    testapi31.publisher.cpp
    testapi31.threadsafedecorator.cpp
    testapi32.publisher.cpp
    testapi32.threadsafedecorator.cpp
    testapi33.publisher.cpp
    testapi33.threadsafedecorator.cpp
    testapi34.publisher.cpp
    testapi34.threadsafedecorator.cpp
    testapi35.publisher.cpp
    testapi35.threadsafedecorator.cpp
    testapi36.publisher.cpp
    testapi36.threadsafedecorator.cpp
    testapi37.publisher.cpp
    testapi37.threadsafedecorator.cpp
    testapi38.publisher.cpp
    testapi38.threadsafedecorator.cpp
    testapi39.publisher.cpp
    testapi39.threadsafedecorator.cpp
    testapi40.publisher.cpp
    testapi40.threadsafedecorator.cpp
    testapi41.publisher.cpp
    testapi41.threadsafedecorator.cpp
    testapi42.publisher.cpp
    testapi42.threadsafedecorator.cpp
    testapi43.publisher.cpp
    testapi43.threadsafedecorator.cpp
    testapi44.publisher.cpp
    testapi44.threadsafedecorator.cpp
    testapi45.publisher.cpp
    testapi45.threadsafedecorator.cpp
    testapi46.publisher.cpp
    testapi46.threadsafedecorator.cpp
    testapi47.publisher.cpp
    testapi47.threadsafedecorator.cpp
    testapi48.publisher.cpp
    testapi48.threadsafedecorator.cpp
    testapi49.publisher.cpp
    testapi49.threadsafedecorator.cpp
    testapi50.publisher.cpp
    testapi50.threadsafedecorator.cpp
    testapi51.publisher.cpp
    testapi51.threadsafedecorator.cpp
    testapi52.publisher.cpp
    testapi52.threadsafedecorator.cpp
    testapi53.publisher.cpp
    testapi53.threadsafedecorator.cpp
    testapi54.publisher.cpp
    testapi54.threadsafedecorator.cpp
    testapi55.publisher.cpp
    testapi55.threadsafedecorator.cpp
    testapi56.publisher.cpp
    testapi56.threadsafedecorator.cpp
    testapi57.publisher.cpp
    testapi57.threadsafedecorator.cpp
    testapi58.publisher.cpp
    testapi58.threadsafedecorator.cpp
    testapi59.publisher.cpp
    testapi59.threadsafedecorator.cpp
    testapi60.publisher.cpp
    testapi60.threadsafedecorator.cpp
    testapi61.publisher.cpp
    testapi61.threadsafedecorator.cpp
    testapi62.publisher.cpp
    testapi62.threadsafedecorator.cpp
    testapi63.publisher.cpp
    testapi63.threadsafedecorator.cpp
    testapi64.publisher.cpp
    testapi64.threadsafedecorator.cpp
    testapi65.publisher.cpp
    testapi65.threadsafedecorator.cpp
    testapi66.publisher.cpp
    testapi66.threadsafedecorator.cpp
    testapi67.publisher.cpp
    testapi67.threadsafedecorator.cpp
    testapi68.publisher.cpp
    testapi68.threadsafedecorator.cpp
    testapi69.publisher.cpp
    testapi69.threadsafedecorator.cpp
    testapi70.publisher.cpp
    testapi70.threadsafedecorator.cpp
    testapi71.publisher.cpp
    testapi71.threadsafedecorator.cpp
    testapi72.publisher.cpp
    testapi72.threadsafedecorator.cpp
    testapi73.publisher.cpp
    testapi73.threadsafedecorator.cpp
    testapi74.publisher.cpp
    testapi74.threadsafedecorator.cpp
    testapi75.publisher.cpp
    testapi75.threadsafedecorator.cpp
    testapi76.publisher.cpp
    testapi76.threadsafedecorator.cpp
    testapi77.publisher.cpp
    testapi77.threadsafedecorator.cpp
    testapi78.publisher.cpp
    testapi78.threadsafedecorator.cpp
    testapi79.publisher.cpp
    testapi79.threadsafedecorator.cpp
    testapi80.publisher.cpp
    testapi80.threadsafedecorator.cpp
    testapi81.publisher.cpp
    testapi81.threadsafedecorator.cpp
    testapi82.publisher.cpp
    testapi82.threadsafedecorator.cpp
    testapi83.publisher.cpp
    testapi83.threadsafedecorator.cpp
    testapi84.publisher.cpp
    testapi84.threadsafedecorator.cpp
    testapi85.publisher.cpp
    testapi85.threadsafedecorator.cpp
    testapi86.publisher.cpp
    testapi86.threadsafedecorator.cpp
    testapi87.publisher.cpp
    testapi87.threadsafedecorator.cpp
    testapi88.publisher.cpp
    testapi88.threadsafedecorator.cpp
    testapi89.publisher.cpp
    testapi89.threadsafedecorator.cpp
    testapi90.publisher.cpp
    testapi90.threadsafedecorator.cpp
    testapi91.publisher.cpp
    testapi91.threadsafedecorator.cpp
    testapi92.publisher.cpp
    testapi92.threadsafedecorator.cpp
    testapi93.publisher.cpp
    testapi93.threadsafedecorator.cpp
    testapi94.publisher.cpp
    testapi94.threadsafedecorator.cpp
    testapi95.publisher.cpp
    testapi95.threadsafedecorator.cpp
    testapi96.publisher.cpp
    testapi96.threadsafedecorator.cpp
    testapi97.publisher.cpp
    testapi97.threadsafedecorator.cpp
    testapi98.publisher.cpp
    testapi98.threadsafedecorator.cpp
    testapi99.publisher.cpp
    testapi99.threadsafedecorator.cpp
)
add_library(api-core SHARED ${SOURCES_CORE_SUPPORT})
add_library(api::api-core ALIAS api-core)
target_include_directories(api-core
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../modules>
    $<INSTALL_INTERFACE:include/api>
)
target_link_libraries(api-core PUBLIC api::api-api nlohmann_json::nlohmann_json)
# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(api-core PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(api-core PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS api-core
        EXPORT ApiCoreTargets
        RUNTIME DESTINATION bin                 COMPONENT Runtime
        LIBRARY DESTINATION lib                 COMPONENT Runtime
        ARCHIVE DESTINATION lib/api   COMPONENT Development)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/api/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT ApiCoreTargets
  NAMESPACE api::
)

install(EXPORT ApiCoreTargets
  FILE ApiCoreTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE api::
)
