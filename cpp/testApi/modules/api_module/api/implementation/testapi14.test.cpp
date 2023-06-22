#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi14.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi14", "[TestApi14]"){
    std::unique_ptr<ITestApi14> testTestApi14 = std::make_unique<TestApi14>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi14->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi14->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi14->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi14->setPropInt(0);
        REQUIRE( testTestApi14->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi14->setPropFloat(0.0f);
        REQUIRE( testTestApi14->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi14->setPropString(std::string());
        REQUIRE( testTestApi14->getPropString() == std::string() );
    }
}
