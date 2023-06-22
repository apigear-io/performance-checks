#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi15.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi15", "[TestApi15]"){
    std::unique_ptr<ITestApi15> testTestApi15 = std::make_unique<TestApi15>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi15->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi15->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi15->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi15->setPropInt(0);
        REQUIRE( testTestApi15->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi15->setPropFloat(0.0f);
        REQUIRE( testTestApi15->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi15->setPropString(std::string());
        REQUIRE( testTestApi15->getPropString() == std::string() );
    }
}
