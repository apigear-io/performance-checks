#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi75.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi75", "[TestApi75]"){
    std::unique_ptr<ITestApi75> testTestApi75 = std::make_unique<TestApi75>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi75->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi75->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi75->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi75->setPropInt(0);
        REQUIRE( testTestApi75->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi75->setPropFloat(0.0f);
        REQUIRE( testTestApi75->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi75->setPropString(std::string());
        REQUIRE( testTestApi75->getPropString() == std::string() );
    }
}
