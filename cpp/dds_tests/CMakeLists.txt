cmake_minimum_required(VERSION 3.1)
project(olink_single_object_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF)


#list(APPEND CMAKE_PREFIX_PATH  "C:/siili/dds/cyclonedds/deps")
#find_package(CycloneDDS REQUIRED)

find_package(fastdds REQUIRED)

find_package(apigear REQUIRED COMPONENT utilities)

find_package(api COMPONENTS  api-implementation api-core)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(dds_single_client_syncSetIntProperty "client_syncSetIntProperty.cpp" "../latency_helpers/latency_helpers.cpp" "types/HelloWorld.cxx"  "types/HelloWorldPubSubTypes.cxx"  "dds_client.cpp"   "apigear/client_publisher.cpp" "apigear/client_subscriber.cpp" "types/sample.cxx" "types/samplePubSubTypes.cxx" "types/sampleCdrAux.ipp" "types/sampleTypeObject.cxx")
add_executable(dds_single_service "server.cpp" "../latency_helpers/latency_helpers.cpp" "types/HelloWorld.cxx"  "types/HelloWorldPubSubTypes.cxx"  "dds_service.cpp"    "apigear/service_publisher.cpp" "apigear/service_subscriber.cpp" "types/sample.cxx" "types/samplePubSubTypes.cxx" "types/sampleCdrAux.ipp" "types/sampleTypeObject.cxx")

target_link_libraries(dds_single_client_syncSetIntProperty api::api-implementation api::api-core fast-dds::fast-dds apigear::utilities)
target_link_libraries(dds_single_service api::api-implementation fast-dds::fast-dds api::api-core apigear::utilities)

