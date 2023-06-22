#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi6.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi6", "[TestApi6]"){
    std::unique_ptr<ITestApi6> testTestApi6 = std::make_unique<TestApi6>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi6->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi6->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi6->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi6->setPropInt(0);
        REQUIRE( testTestApi6->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi6->setPropFloat(0.0f);
        REQUIRE( testTestApi6->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi6->setPropString(std::string());
        REQUIRE( testTestApi6->getPropString() == std::string() );
    }
}
