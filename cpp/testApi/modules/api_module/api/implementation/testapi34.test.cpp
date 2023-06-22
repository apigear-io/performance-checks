#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi34.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi34", "[TestApi34]"){
    std::unique_ptr<ITestApi34> testTestApi34 = std::make_unique<TestApi34>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi34->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi34->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi34->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi34->setPropInt(0);
        REQUIRE( testTestApi34->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi34->setPropFloat(0.0f);
        REQUIRE( testTestApi34->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi34->setPropString(std::string());
        REQUIRE( testTestApi34->getPropString() == std::string() );
    }
}
