#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi71.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi71", "[TestApi71]"){
    std::unique_ptr<ITestApi71> testTestApi71 = std::make_unique<TestApi71>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi71->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi71->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi71->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi71->setPropInt(0);
        REQUIRE( testTestApi71->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi71->setPropFloat(0.0f);
        REQUIRE( testTestApi71->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi71->setPropString(std::string());
        REQUIRE( testTestApi71->getPropString() == std::string() );
    }
}
