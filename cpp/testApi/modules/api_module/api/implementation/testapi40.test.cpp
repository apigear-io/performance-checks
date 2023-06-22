#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi40.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi40", "[TestApi40]"){
    std::unique_ptr<ITestApi40> testTestApi40 = std::make_unique<TestApi40>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi40->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi40->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi40->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi40->setPropInt(0);
        REQUIRE( testTestApi40->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi40->setPropFloat(0.0f);
        REQUIRE( testTestApi40->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi40->setPropString(std::string());
        REQUIRE( testTestApi40->getPropString() == std::string() );
    }
}
