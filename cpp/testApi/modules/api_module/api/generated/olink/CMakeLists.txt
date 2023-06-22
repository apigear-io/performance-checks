set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(apigear QUIET COMPONENTS poco-olink)
set (SOURCES_OLINK
    testapi0service.cpp
    testapi0client.cpp
    testapi1service.cpp
    testapi1client.cpp
    testapi2service.cpp
    testapi2client.cpp
    testapi3service.cpp
    testapi3client.cpp
    testapi4service.cpp
    testapi4client.cpp
    testapi5service.cpp
    testapi5client.cpp
    testapi6service.cpp
    testapi6client.cpp
    testapi7service.cpp
    testapi7client.cpp
    testapi8service.cpp
    testapi8client.cpp
    testapi9service.cpp
    testapi9client.cpp
    testapi10service.cpp
    testapi10client.cpp
    testapi11service.cpp
    testapi11client.cpp
    testapi12service.cpp
    testapi12client.cpp
    testapi13service.cpp
    testapi13client.cpp
    testapi14service.cpp
    testapi14client.cpp
    testapi15service.cpp
    testapi15client.cpp
    testapi16service.cpp
    testapi16client.cpp
    testapi17service.cpp
    testapi17client.cpp
    testapi18service.cpp
    testapi18client.cpp
    testapi19service.cpp
    testapi19client.cpp
    testapi20service.cpp
    testapi20client.cpp
    testapi21service.cpp
    testapi21client.cpp
    testapi22service.cpp
    testapi22client.cpp
    testapi23service.cpp
    testapi23client.cpp
    testapi24service.cpp
    testapi24client.cpp
    testapi25service.cpp
    testapi25client.cpp
    testapi26service.cpp
    testapi26client.cpp
    testapi27service.cpp
    testapi27client.cpp
    testapi28service.cpp
    testapi28client.cpp
    testapi29service.cpp
    testapi29client.cpp
    testapi30service.cpp
    testapi30client.cpp
    testapi31service.cpp
    testapi31client.cpp
    testapi32service.cpp
    testapi32client.cpp
    testapi33service.cpp
    testapi33client.cpp
    testapi34service.cpp
    testapi34client.cpp
    testapi35service.cpp
    testapi35client.cpp
    testapi36service.cpp
    testapi36client.cpp
    testapi37service.cpp
    testapi37client.cpp
    testapi38service.cpp
    testapi38client.cpp
    testapi39service.cpp
    testapi39client.cpp
    testapi40service.cpp
    testapi40client.cpp
    testapi41service.cpp
    testapi41client.cpp
    testapi42service.cpp
    testapi42client.cpp
    testapi43service.cpp
    testapi43client.cpp
    testapi44service.cpp
    testapi44client.cpp
    testapi45service.cpp
    testapi45client.cpp
    testapi46service.cpp
    testapi46client.cpp
    testapi47service.cpp
    testapi47client.cpp
    testapi48service.cpp
    testapi48client.cpp
    testapi49service.cpp
    testapi49client.cpp
    testapi50service.cpp
    testapi50client.cpp
    testapi51service.cpp
    testapi51client.cpp
    testapi52service.cpp
    testapi52client.cpp
    testapi53service.cpp
    testapi53client.cpp
    testapi54service.cpp
    testapi54client.cpp
    testapi55service.cpp
    testapi55client.cpp
    testapi56service.cpp
    testapi56client.cpp
    testapi57service.cpp
    testapi57client.cpp
    testapi58service.cpp
    testapi58client.cpp
    testapi59service.cpp
    testapi59client.cpp
    testapi60service.cpp
    testapi60client.cpp
    testapi61service.cpp
    testapi61client.cpp
    testapi62service.cpp
    testapi62client.cpp
    testapi63service.cpp
    testapi63client.cpp
    testapi64service.cpp
    testapi64client.cpp
    testapi65service.cpp
    testapi65client.cpp
    testapi66service.cpp
    testapi66client.cpp
    testapi67service.cpp
    testapi67client.cpp
    testapi68service.cpp
    testapi68client.cpp
    testapi69service.cpp
    testapi69client.cpp
    testapi70service.cpp
    testapi70client.cpp
    testapi71service.cpp
    testapi71client.cpp
    testapi72service.cpp
    testapi72client.cpp
    testapi73service.cpp
    testapi73client.cpp
    testapi74service.cpp
    testapi74client.cpp
    testapi75service.cpp
    testapi75client.cpp
    testapi76service.cpp
    testapi76client.cpp
    testapi77service.cpp
    testapi77client.cpp
    testapi78service.cpp
    testapi78client.cpp
    testapi79service.cpp
    testapi79client.cpp
    testapi80service.cpp
    testapi80client.cpp
    testapi81service.cpp
    testapi81client.cpp
    testapi82service.cpp
    testapi82client.cpp
    testapi83service.cpp
    testapi83client.cpp
    testapi84service.cpp
    testapi84client.cpp
    testapi85service.cpp
    testapi85client.cpp
    testapi86service.cpp
    testapi86client.cpp
    testapi87service.cpp
    testapi87client.cpp
    testapi88service.cpp
    testapi88client.cpp
    testapi89service.cpp
    testapi89client.cpp
    testapi90service.cpp
    testapi90client.cpp
    testapi91service.cpp
    testapi91client.cpp
    testapi92service.cpp
    testapi92client.cpp
    testapi93service.cpp
    testapi93client.cpp
    testapi94service.cpp
    testapi94client.cpp
    testapi95service.cpp
    testapi95client.cpp
    testapi96service.cpp
    testapi96client.cpp
    testapi97service.cpp
    testapi97client.cpp
    testapi98service.cpp
    testapi98client.cpp
    testapi99service.cpp
    testapi99client.cpp
)
add_library(api-olink SHARED ${SOURCES_OLINK})
add_library(api::api-olink ALIAS api-olink)
target_include_directories(api-olink
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../../../modules>
    $<INSTALL_INTERFACE:include/api>
)
target_link_libraries(api-olink 
    api::api-core
    apigear::poco-olink
)

# ensure maximum compiler support
if(NOT MSVC)
  target_compile_options(api-olink PRIVATE -Wall -Wextra -Wpedantic -Werror -fvisibility=hidden)
else()
  target_compile_options(api-olink PRIVATE /W4 /WX /wd4251)
endif()

install(TARGETS api-olink
        EXPORT ApiOLinkTargets
        RUNTIME DESTINATION bin                 COMPONENT Runtime
        LIBRARY DESTINATION lib                 COMPONENT Runtime
        ARCHIVE DESTINATION lib/api   COMPONENT Development)
# install includes
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/api/generated FILES_MATCHING PATTERN "*.h")

export(EXPORT ApiOLinkTargets
  NAMESPACE api::
)

install(EXPORT ApiOLinkTargets
  FILE ApiOLinkTargets.cmake
  DESTINATION ${InstallDir}
  NAMESPACE api::
)
