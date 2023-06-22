#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi19.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi19", "[TestApi19]"){
    std::unique_ptr<ITestApi19> testTestApi19 = std::make_unique<TestApi19>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi19->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi19->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi19->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi19->setPropInt(0);
        REQUIRE( testTestApi19->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi19->setPropFloat(0.0f);
        REQUIRE( testTestApi19->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi19->setPropString(std::string());
        REQUIRE( testTestApi19->getPropString() == std::string() );
    }
}
