#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi17.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi17", "[TestApi17]"){
    std::unique_ptr<ITestApi17> testTestApi17 = std::make_unique<TestApi17>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi17->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi17->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi17->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi17->setPropInt(0);
        REQUIRE( testTestApi17->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi17->setPropFloat(0.0f);
        REQUIRE( testTestApi17->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi17->setPropString(std::string());
        REQUIRE( testTestApi17->getPropString() == std::string() );
    }
}
