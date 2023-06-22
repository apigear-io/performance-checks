#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi86.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi86", "[TestApi86]"){
    std::unique_ptr<ITestApi86> testTestApi86 = std::make_unique<TestApi86>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi86->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi86->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi86->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi86->setPropInt(0);
        REQUIRE( testTestApi86->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi86->setPropFloat(0.0f);
        REQUIRE( testTestApi86->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi86->setPropString(std::string());
        REQUIRE( testTestApi86->getPropString() == std::string() );
    }
}
