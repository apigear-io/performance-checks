#include <memory>
#include "catch2/catch.hpp"
#include "api/implementation/testapi77.h"

using namespace Cpp::Api;
TEST_CASE("Testing TestApi77", "[TestApi77]"){
    std::unique_ptr<ITestApi77> testTestApi77 = std::make_unique<TestApi77>();
    // setup your test
    SECTION("Test operation funcInt") {
        // Do implement test here
        testTestApi77->funcInt(0);
    }
    SECTION("Test operation funcFloat") {
        // Do implement test here
        testTestApi77->funcFloat(0.0f);
    }
    SECTION("Test operation funcString") {
        // Do implement test here
        testTestApi77->funcString(std::string());
    }
    SECTION("Test property propInt") {
        // Do implement test here
        testTestApi77->setPropInt(0);
        REQUIRE( testTestApi77->getPropInt() == 0 );
    }
    SECTION("Test property propFloat") {
        // Do implement test here
        testTestApi77->setPropFloat(0.0f);
        REQUIRE( testTestApi77->getPropFloat() == Approx( 0.0f ) );
    }
    SECTION("Test property propString") {
        // Do implement test here
        testTestApi77->setPropString(std::string());
        REQUIRE( testTestApi77->getPropString() == std::string() );
    }
}
