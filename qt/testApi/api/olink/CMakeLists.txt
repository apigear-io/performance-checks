project(api_olink)

find_package(Qt5 REQUIRED COMPONENTS Core)

set (API_OLINK_SOURCES
    olinkfactory.cpp
    olinktestapi0.cpp
    olinktestapi0adapter.cpp
    olinktestapi1.cpp
    olinktestapi1adapter.cpp
    olinktestapi2.cpp
    olinktestapi2adapter.cpp
    olinktestapi3.cpp
    olinktestapi3adapter.cpp
    olinktestapi4.cpp
    olinktestapi4adapter.cpp
    olinktestapi5.cpp
    olinktestapi5adapter.cpp
    olinktestapi6.cpp
    olinktestapi6adapter.cpp
    olinktestapi7.cpp
    olinktestapi7adapter.cpp
    olinktestapi8.cpp
    olinktestapi8adapter.cpp
    olinktestapi9.cpp
    olinktestapi9adapter.cpp
    olinktestapi10.cpp
    olinktestapi10adapter.cpp
    olinktestapi11.cpp
    olinktestapi11adapter.cpp
    olinktestapi12.cpp
    olinktestapi12adapter.cpp
    olinktestapi13.cpp
    olinktestapi13adapter.cpp
    olinktestapi14.cpp
    olinktestapi14adapter.cpp
    olinktestapi15.cpp
    olinktestapi15adapter.cpp
    olinktestapi16.cpp
    olinktestapi16adapter.cpp
    olinktestapi17.cpp
    olinktestapi17adapter.cpp
    olinktestapi18.cpp
    olinktestapi18adapter.cpp
    olinktestapi19.cpp
    olinktestapi19adapter.cpp
    olinktestapi20.cpp
    olinktestapi20adapter.cpp
    olinktestapi21.cpp
    olinktestapi21adapter.cpp
    olinktestapi22.cpp
    olinktestapi22adapter.cpp
    olinktestapi23.cpp
    olinktestapi23adapter.cpp
    olinktestapi24.cpp
    olinktestapi24adapter.cpp
    olinktestapi25.cpp
    olinktestapi25adapter.cpp
    olinktestapi26.cpp
    olinktestapi26adapter.cpp
    olinktestapi27.cpp
    olinktestapi27adapter.cpp
    olinktestapi28.cpp
    olinktestapi28adapter.cpp
    olinktestapi29.cpp
    olinktestapi29adapter.cpp
    olinktestapi30.cpp
    olinktestapi30adapter.cpp
    olinktestapi31.cpp
    olinktestapi31adapter.cpp
    olinktestapi32.cpp
    olinktestapi32adapter.cpp
    olinktestapi33.cpp
    olinktestapi33adapter.cpp
    olinktestapi34.cpp
    olinktestapi34adapter.cpp
    olinktestapi35.cpp
    olinktestapi35adapter.cpp
    olinktestapi36.cpp
    olinktestapi36adapter.cpp
    olinktestapi37.cpp
    olinktestapi37adapter.cpp
    olinktestapi38.cpp
    olinktestapi38adapter.cpp
    olinktestapi39.cpp
    olinktestapi39adapter.cpp
    olinktestapi40.cpp
    olinktestapi40adapter.cpp
    olinktestapi41.cpp
    olinktestapi41adapter.cpp
    olinktestapi42.cpp
    olinktestapi42adapter.cpp
    olinktestapi43.cpp
    olinktestapi43adapter.cpp
    olinktestapi44.cpp
    olinktestapi44adapter.cpp
    olinktestapi45.cpp
    olinktestapi45adapter.cpp
    olinktestapi46.cpp
    olinktestapi46adapter.cpp
    olinktestapi47.cpp
    olinktestapi47adapter.cpp
    olinktestapi48.cpp
    olinktestapi48adapter.cpp
    olinktestapi49.cpp
    olinktestapi49adapter.cpp
    olinktestapi50.cpp
    olinktestapi50adapter.cpp
    olinktestapi51.cpp
    olinktestapi51adapter.cpp
    olinktestapi52.cpp
    olinktestapi52adapter.cpp
    olinktestapi53.cpp
    olinktestapi53adapter.cpp
    olinktestapi54.cpp
    olinktestapi54adapter.cpp
    olinktestapi55.cpp
    olinktestapi55adapter.cpp
    olinktestapi56.cpp
    olinktestapi56adapter.cpp
    olinktestapi57.cpp
    olinktestapi57adapter.cpp
    olinktestapi58.cpp
    olinktestapi58adapter.cpp
    olinktestapi59.cpp
    olinktestapi59adapter.cpp
    olinktestapi60.cpp
    olinktestapi60adapter.cpp
    olinktestapi61.cpp
    olinktestapi61adapter.cpp
    olinktestapi62.cpp
    olinktestapi62adapter.cpp
    olinktestapi63.cpp
    olinktestapi63adapter.cpp
    olinktestapi64.cpp
    olinktestapi64adapter.cpp
    olinktestapi65.cpp
    olinktestapi65adapter.cpp
    olinktestapi66.cpp
    olinktestapi66adapter.cpp
    olinktestapi67.cpp
    olinktestapi67adapter.cpp
    olinktestapi68.cpp
    olinktestapi68adapter.cpp
    olinktestapi69.cpp
    olinktestapi69adapter.cpp
    olinktestapi70.cpp
    olinktestapi70adapter.cpp
    olinktestapi71.cpp
    olinktestapi71adapter.cpp
    olinktestapi72.cpp
    olinktestapi72adapter.cpp
    olinktestapi73.cpp
    olinktestapi73adapter.cpp
    olinktestapi74.cpp
    olinktestapi74adapter.cpp
    olinktestapi75.cpp
    olinktestapi75adapter.cpp
    olinktestapi76.cpp
    olinktestapi76adapter.cpp
    olinktestapi77.cpp
    olinktestapi77adapter.cpp
    olinktestapi78.cpp
    olinktestapi78adapter.cpp
    olinktestapi79.cpp
    olinktestapi79adapter.cpp
    olinktestapi80.cpp
    olinktestapi80adapter.cpp
    olinktestapi81.cpp
    olinktestapi81adapter.cpp
    olinktestapi82.cpp
    olinktestapi82adapter.cpp
    olinktestapi83.cpp
    olinktestapi83adapter.cpp
    olinktestapi84.cpp
    olinktestapi84adapter.cpp
    olinktestapi85.cpp
    olinktestapi85adapter.cpp
    olinktestapi86.cpp
    olinktestapi86adapter.cpp
    olinktestapi87.cpp
    olinktestapi87adapter.cpp
    olinktestapi88.cpp
    olinktestapi88adapter.cpp
    olinktestapi89.cpp
    olinktestapi89adapter.cpp
    olinktestapi90.cpp
    olinktestapi90adapter.cpp
    olinktestapi91.cpp
    olinktestapi91adapter.cpp
    olinktestapi92.cpp
    olinktestapi92adapter.cpp
    olinktestapi93.cpp
    olinktestapi93adapter.cpp
    olinktestapi94.cpp
    olinktestapi94adapter.cpp
    olinktestapi95.cpp
    olinktestapi95adapter.cpp
    olinktestapi96.cpp
    olinktestapi96adapter.cpp
    olinktestapi97.cpp
    olinktestapi97adapter.cpp
    olinktestapi98.cpp
    olinktestapi98adapter.cpp
    olinktestapi99.cpp
    olinktestapi99adapter.cpp
)

add_library(api_olink STATIC ${API_OLINK_SOURCES})
add_library(api::api_olink ALIAS api_olink)
target_include_directories(api_olink
    PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../>
    $<INSTALL_INTERFACE:include/api>
)

target_link_libraries(api_olink PUBLIC api::api_api olink_qt qtpromise)
