#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi83.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi83", "[TestApi83]"){
    std::unique_ptr<ITestApi83> testTestApi83 = std::make_unique<TestApi83>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi83->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi83->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi83->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi83->setPropInt(0);
        REQUIRE( testTestApi83->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi83->setPropFloat(0.0f);
        REQUIRE( testTestApi83->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi83->setPropString(std::string());
        REQUIRE( testTestApi83->getPropString() == std::string() );
    }
}
