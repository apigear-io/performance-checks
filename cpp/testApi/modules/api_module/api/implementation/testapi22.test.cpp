#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi22.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi22", "[TestApi22]"){
    std::unique_ptr<ITestApi22> testTestApi22 = std::make_unique<TestApi22>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi22->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi22->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi22->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi22->setPropInt(0);
        REQUIRE( testTestApi22->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi22->setPropFloat(0.0f);
        REQUIRE( testTestApi22->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi22->setPropString(std::string());
        REQUIRE( testTestApi22->getPropString() == std::string() );
    }
}
