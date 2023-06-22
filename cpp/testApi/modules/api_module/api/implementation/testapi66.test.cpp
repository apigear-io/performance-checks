#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi66.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi66", "[TestApi66]"){
    std::unique_ptr<ITestApi66> testTestApi66 = std::make_unique<TestApi66>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi66->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi66->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi66->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi66->setPropInt(0);
        REQUIRE( testTestApi66->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi66->setPropFloat(0.0f);
        REQUIRE( testTestApi66->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi66->setPropString(std::string());
        REQUIRE( testTestApi66->getPropString() == std::string() );
    }
}
