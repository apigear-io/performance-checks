#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi16.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi16", "[TestApi16]"){
    std::unique_ptr<ITestApi16> testTestApi16 = std::make_unique<TestApi16>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi16->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi16->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi16->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi16->setPropInt(0);
        REQUIRE( testTestApi16->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi16->setPropFloat(0.0f);
        REQUIRE( testTestApi16->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi16->setPropString(std::string());
        REQUIRE( testTestApi16->getPropString() == std::string() );
    }
}
