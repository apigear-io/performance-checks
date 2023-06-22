#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi81.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi81", "[TestApi81]"){
    std::unique_ptr<ITestApi81> testTestApi81 = std::make_unique<TestApi81>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi81->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi81->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi81->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi81->setPropInt(0);
        REQUIRE( testTestApi81->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi81->setPropFloat(0.0f);
        REQUIRE( testTestApi81->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi81->setPropString(std::string());
        REQUIRE( testTestApi81->getPropString() == std::string() );
    }
}
